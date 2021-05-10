#pragma once
#include "ITree.h"

class RBTree : public ITree {
public:
	void getBalance() {
		Node* node = root;
		if (node == null) return;
		int n = 0;
		if (root->color == BLACK) n++;
		getBalance(root, n);
	}
private:
	void getBalance(Node* node, int count) {
		if (node == null) {
			std::cout << count << " ";
			return;
		}
		if (node->color == BLACK) count++;
		getBalance(node->left, count);
		getBalance(node->right, count);
	}

#pragma region ADDING_NODES
	Node* t_add(int data) override {
		if (root == null) {
			root = new Node(data);
			return root;
		}
		Node* tmp = root;
		for (;;) {
			if (tmp->data > data) {
				if (tmp->left == null) {
					tmp->left = new Node(data, tmp);
					return tmp->left;
				}
				tmp = tmp->left;
			}
			else if (tmp->data < data) {
				if (tmp->right == null) {
					tmp->right = new Node(data, tmp);
					return tmp->right;
				}
				tmp = tmp->right;
			}
			else
				return null;
		}
	}

	void add_action(Node* node) override {
		t_size++;
		node->color = RED;
		add_balance(node);
		root->color = BLACK;
	}

	void add_balance(Node* node) {
		if (node == null)
			return;
		if (node == root) {
			node->color = BLACK;
#ifdef DEBUG
			std::cout << "Node is root, marking as black\n";
#endif
			return;
		}
		if (node->parent == null)
			return;
		if (node->parent->color == BLACK) {
#ifdef DEBUG
			std::cout << "Node's father is black, no actions needed\n";
#endif
			return;
		}
		if (node->parent->parent == null)
			return;
		if (node->color == BLACK || node->parent->color == BLACK)
			return;
#ifdef DEBUG
		std::cout << "Violation occured: duplication of red nodes\n";
#endif
		if (getUncleColor(node) == RED) {
#ifdef DEBUG
			std::cout << "Node's uncle is red: remarking\n";
#endif 
			node->parent->color = BLACK;
			if (node->parent->parent != root)
				node->parent->parent->color = RED;
			if (getUncle(node) != null)
				getUncle(node)->color = BLACK;
			add_balance(node->parent->parent);
			return;
		}
#ifdef DEBUG
		std::cout << "Node's uncle is black: moving\n";
#endif
		Node* grandfather = node->parent->parent;
		Node* father = node->parent;
		if(grandfather->right != null)
		if (grandfather->right->left == node) {
#ifdef DEBUG
			std::cout << "Triangle moment on right side\n";
#endif
			Node* tmp = node->right;
			grandfather->right = node;
			node->parent = grandfather;
			node->right = father;
			father->parent = node;
			father->left = tmp;
			if (tmp != null)
				tmp->parent = father;
			add_balance(father);
			return;
		}
		if (grandfather->left != null)
		if (grandfather->left->right == node) {
#ifdef DEBUG
			std::cout << "Triangle moment on left side\n";
#endif
			Node* tmp = node->left;
			grandfather->left = node;
			node->parent = grandfather;
			node->left = father;
			father->parent = node;
			father->right = tmp;
			if (tmp != null)
				tmp->parent = father;
			add_balance(father);
			return;
		}
		if (grandfather->right != null)
		if (grandfather->right->right == node) {
#ifdef DEBUG
			std::cout << "Linear moment on right side\n";
#endif
			Node* X = node;
			Node* A = node->parent;
			Node* B = node->parent->parent;
			Node* C = node->parent->parent->left;
			Node* y = A->left;
			if (B->parent == null) {
				root = A;
				root->parent = null;
			} else {
				B->getNode() = A;
				A->parent = B->parent;
			}
			A->left = B;
			A->right = X;
			B->left = C;
			B->right = y;
			B->parent = A;
			if (y != null)
				y->parent = B;
			A->color = BLACK;
			B->color = RED;
			X->color = RED;
			if (C != null)
				C->color = BLACK;
			add_balance(A);
			return;
		}
		if (grandfather->left != null)
		if (grandfather->left->left == node) {
#ifdef DEBUG
			std::cout << "Linear moment on left side\n";
#endif
			Node* X = node;
			Node* A = node->parent;
			Node* B = node->parent->parent;
			Node* C = node->parent->parent->right;
			Node* y = A->right;
			if (B->parent == null) {
				root = A;
				root->parent = null;
			} else {
				B->getNode() = A;
				A->parent = B->parent;
			}
			A->right = B;
			A->left = X;
			B->right = C;
			B->left = y;
			B->parent = A;
			if (y != null)
				y->parent = B;
			A->color = BLACK;
			B->color = RED;
			X->color = RED;
			if (C != null)
				C->color = BLACK;
			add_balance(A);
			return;
		}
	}
#pragma endregion

#pragma region REMOVING_NODES
	Node* t_remove(int data) override {
		Node* ob = this->find(data);
		if (ob == null)
			return null;
		if (ob == root && root->isLeaf()) {
#ifdef DEBUG
			std::cout << "Removing root\n";
#endif
			root = null;
			return null;
		}
		return r_remove(ob);
	}

	Node* r_remove(Node* node) {
		if (node->left != null && node->right != null) {
#ifdef DEBUG
			std::cout << "Node has two sons: moving forward and swapping\n";
#endif
			Node* tmp = node->left;
			for (; tmp->right != null; tmp = tmp->right);
#ifdef DEBUG
			std::cout << "Node has two sons, moving forward and swapping:\n" << node->getInfo() << "\n" << tmp->getInfo() << "\n\n";
#endif
			dswap(node, tmp);
			return r_remove(tmp);
		}
		if (node->color == RED && node->isLeaf()) {
#ifdef DEBUG
			std::cout << "Node is red" << node->getInfo() << "\nand doesn't have sons, removing\n\n";
#endif
			node->getNode() = null;
			delete node;
			return null;
		}
		if (node->color == RED && !node->isLeaf())
			throw std::exception("4to-to poshlo po pizde");
		if (node->color == BLACK && !node->isLeaf()) {
#ifdef DEBUG
			std::cout << "Node is black and has one son: moving forward and swapping\n";
#endif
			if (node->left != null) {
				Node* tmp = node->left;
				for (; tmp->right != null; tmp = tmp->right);
#ifdef DEBUG
				std::cout << node->getInfo() << "\n" << tmp->getInfo() << "\n\n";
#endif
				dswap(node, tmp);
				return r_remove(tmp);
			} else {
				Node* tmp = node->right;
				for (; tmp->left != null; tmp = tmp->left);
#ifdef DEBUG
				std::cout << node->getInfo() << "\n" << tmp->getInfo() << "\n\n";
#endif
				dswap(node, tmp);
				return r_remove(tmp);
			}
		}
		//Ahahaha ya neuravnovesheniy mne nuzhno v izolyator)))
		if (node->color == BLACK && node->isLeaf()) {
			node->getNode() = null;
			Node* tmp = node->parent;
			delete node;
			remove_balance(tmp);
		}
		return null;
	}

	//Фиксы и допилить зеркальную операцию
	void remove_balance(Node* node) {
		if (node->right != null)
			throw std::exception("AMOGUS");
		Node* son = node->left;
		if (node->color == RED && son->color == BLACK) {
#ifdef DEBUG
			std::cout << "Parent is red and son is black\n";
#endif
			bool lb = son->left == null, rb = son->right == null;
			if (!lb) lb = son->left->color == BLACK;
			if (!rb) rb = son->right->color == BLACK;
			if (lb && rb) {
#ifdef DEBUG
				std::cout << "Grandsons are black: recoloring\n";
#endif
				node->color = RED;
				son->color = BLACK;
				return;
			}
			if (!lb) {
#ifdef DEBUG
				std::cout << "Left grandson is red: moving\n";
#endif
				Node* A = node;
				Node* B = node->left;
				Node* C = node->left->left;
				Node* D = node->left->right;
				if (A == root) {
					root = B;
					B->parent = null;
				} else {
					A->getNode() = B;
					B->parent = A->parent;
				}
				B->left = C;
				B->right = A;
				C->parent = B;
				A->parent = B;
				A->left = D;
				if (D != null)
					D->parent = A;
				C->color = BLACK;
				B->color = RED;
				A->color = BLACK;
				return;
			}
			if (!rb) {
#ifdef DEBUG
				std::cout << "Right grandson is red: moving\n";
#endif
				Node* A = node;
				Node* B = node->left;
				Node* C = node->left->left;
				Node* D = node->left->right;
				Node* E = node->left->right->left;
				Node* F = node->left->right->right;
				if (A == root) {
					root = D;
					D->parent = null;
				}
				else {
					A->getNode() = D;
					D->parent = A->parent;
				}
				D->left = B;
				D->right = A;
				B->left = C;
				B->right = E;
				B->parent = D;
				A->left = F;
				A->right = null;
				A->parent = D;
				if (C != null)
					C->parent = B;
				if (E != null)
					E->parent = B;
				if (F != null)
					F->parent = A;
				return;
			}
		}
		if (node->color == BLACK && son->color == RED) {
#ifdef DEBUG
			std::cout << "Node color is black and son color is red\n";
#endif
			bool lb = son->right->left == null, rb = son->right->right == null;
			if (!lb) lb = son->right->left->color == BLACK;
			if (!rb) rb = son->right->right->color == BLACK;
			if (lb && rb) {
#ifdef DEBUG
				std::cout << "Grandsons are black: moving\n";
#endif
				Node* A = node;
				Node* B = node->left;
				Node* C = node->left->right;
				if (A == root) {
					root = B;
					B->parent = null;
				} else {
					A->getNode() = B;
					B->parent = A->parent;
				}
				B->right = A;
				A->parent = B;
				A->left = C;
				C->parent = A;
				B->color = BLACK;
				A->color = BLACK;
				C->color = RED;
				return;
			}
			if (!lb) {
#ifdef DEBUG
				std::cout << "Left grandson is red: moving\n";
#endif
				Node* A = node;
				Node* B = node->left;
				Node* C = node->left->right;
				Node* D = node->left->right->left;          
				Node* E = node->left->right->right;     
				if (A == root) {
					root = C;
					C->parent = null;
				}
				else {
					A->getNode() = C;
					C->parent = A->parent;
				}
				C->left = B;
				C->right = A;
				B->right = D;
				B->parent = C;
				A->left = E;
				A->parent = C;
				D->parent = B;
				if (E != null)
					E->parent = D;
				C->color = BLACK;
				B->color = RED;
				D->color = BLACK;
				A->color = BLACK;
				return;
			}
		}
		if (node->color = BLACK && son->color == BLACK) {
#ifdef DEBUG
			std::cout << "Node and son color are both black\n";
#endif
			if (son->right != null) {
				if (son->right->color == RED) {
#ifdef DEBUG
					std::cout << "Right grandson is red: moving\n";
#endif
					Node* A = node;
					Node* B = node->left;
					Node* C = node->left->left;
					Node* D = node->left->right;
					Node* E = node->left->right->left;
					Node* F = node->left->right->right;
					if (A == root) {
						root = D;
						D->parent = null;
					} else {
						A->getNode() = D;
						D->parent = A->parent;
					}
					D->left = B;
					D->right = A;
					B->parent = D;
					B->left = C;
					B->right = E;
					A->parent = D;
					A->left = F;
					if (C != null)
						C->parent = B;
					if (E != null)
						E->parent = B;
					if (F != null)
						F->parent = A;
					A->color = BLACK;
					B->color = BLACK;
					D->color = BLACK;
					return;
				}
			}
			bool lb = son->left == null, rb = son->right == null;
			if (!lb) lb = son->left->color == BLACK;
			if (!rb) rb = son->right->color == BLACK;
			if (lb && rb) {
				son->color = RED;
				if (node == root)
					return;
				for (Node* i = son; ; i = i->parent) {
					if (i->parent == root) {
						if (root->right = i) {
							go(root->left);
							return;
						}
						if (root->left = i) {
							go(root->right);
							return;
						}
					}
				}
			}
		}
		std::cout << "NOT YET\n";
		return;
	}

	void go(Node* node) {
		if (node == null)
			return;
		if (node->color == BLACK) {
			node->color = RED;
			add_balance(node->left);
			add_balance(node->right);
			return;
		}
		go(node->left);
		go(node->right);
	}

	void remove_action(Node* node) override {

	}
#pragma endregion

	int getBrotherColor(Node* node) {
		if (node->parent == null)
			throw std::exception("No parent detected");
		if (node->parent->left == node)
			return node->parent->right == null ? BLACK : node->parent->right->color;
		return node->parent->left == null ? BLACK : node->parent->left->color;
	}

	Node* getBrother(Node* node) {
		if (node->parent == null)
			throw std::exception("No parent detected");
		if (node->parent->left == node)
			return node->parent->right;
		return node->parent->left;
	}

	int getUncleColor(Node* node) {
		if (node->parent == null)
			throw std::exception("No parent node detected");
		if (node->parent->parent == null)
			throw std::exception("No grandparent node detected");
		Node* grand = node->parent->parent;
		Node* father = node->parent;
		if (grand->left == father)
			return grand->right == null ? BLACK : grand->right->color;
		return grand->left == null ? BLACK : grand->left->color;
	}

	Node* getUncle(Node* node) {
		if (node->parent == null)
			throw std::exception("No parent node detected");
		if (node->parent->parent == null)
			throw std::exception("No grandparent node detected");
		Node* grand = node->parent->parent;
		Node* father = node->parent;
		if (grand->left == father)
			return grand->right;
		return grand->left;
	}
};