#pragma once
#include "ITree.h"

//Pain has face

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
#pragma region

#pragma region REMOVING_NODES 
	Node* t_remove(int data) override {
		Node* ob = this->find(data);
		if (ob == null) {
			return null;
		}
		return n_remove(ob);
	}

	Node* n_remove(Node* node) {
		if (!node->isLeaf()) {
			Node* tmp = findNearest(node);
			dswap(node, tmp);
			return n_remove(tmp);
		}
		if (getColor(node) == RED) {
#ifdef DEBUG
			std::cout << "Node for deletion is red: quiting\n";
#endif
			delete_node(node);
			return null;
		}
		Node* tmp = node->parent;
		delete_node(node);
		return tmp;
	}

	void remove_action(Node* node) override {
#ifdef DEBUG
		std::cout << "Black height violation: fixing" << node->getInfo() << "\n";
#endif
		if (node->right == null)
			balance_right(node);
		else
			balance_left(node);
	}

	void balance_right(Node* node, bool rebalance = false) {
		Node* father = node;
		Node* son = node->left;
#ifdef DEBUG
		std::cout << "Right balance\n";
		std::cout << "\nFather's color is " << (getColor(father) == BLACK ? "black" : "red") << "\n";
		std::cout << "Son's color is " << (getColor(son) == BLACK ? "black" : "red") << "\n";
		std::cout << "Left grandson's color is " << (getColor(son->left) == BLACK ? "black" : "red") << "\n";
		std::cout << "Right grandson's color is " << (getColor(son->right) == BLACK ? "black" : "red") << "\n";
#endif
		if (getColor(father) == RED && getColor(son->left) == BLACK && getColor(son->right) == BLACK) {
#ifdef DEBUG
			std::cout << "[CASE R-RB-1]\n";
#endif 
			father->color = BLACK;
			son->color = RED;
			return;
		}

		if (getColor(father) == RED && getColor(son->left) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-RB-2-L]\n";
#endif 
			rotateRight(father);
			Node* core = father->parent;
			core->color = RED;
			core->left->color = BLACK;
			core->right->color = BLACK;
			return;
		}

		if (getColor(father) == RED && getColor(son->right) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-RB-2-R]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->right;
			Node* D = C->left;
			Node* E = C->right;
			if (A == root) {
				root = C;
				C->parent = null;
			} else {
				A->getNode() = C;
				C->parent = A->parent;
			}
			C->left = B;
			C->right = A;
			C->color = RED;
			B->parent = C;
			B->right = D;
			B->color = BLACK;
			A->parent = C;
			A->left = E;
			A->color = BLACK;
			if (D != null)
				D->parent = B;
			if (E != null)
				E->parent = A;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == RED && getColor(son->right->left) == BLACK && getColor(son->right->right) == BLACK) {
#ifdef DEBUG
			std::cout << "[CASE R-BR-3]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->right;
			if (A == root) {
				root = B;
				B->parent = null;
			}
			else {
				A->getNode() = B;
				B->parent = A->parent;
			}
			B->right = A;
			B->color = BLACK;
			A->parent = B;
			A->left = C;
			A->color = BLACK;
			C->parent = A;
			C->color = RED;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == RED && getColor(son->right->left) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-BR-4-L]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->right;
			Node* D = C->left;
			Node* E = C->right;
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
			C->color = BLACK;
			B->parent = C;
			B->right = D;
			B->color = RED;
			A->parent = C;
			A->left = E;
			A->color = BLACK;
			D->parent = B;
			D->color = BLACK;
			if (E != null)
				E->parent = A;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == RED && getColor(son->right->right) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-BR-4-R]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->right;
			Node* D = C->right;
			if (A == root) {
				root = B;
				B->parent = null;
			}
			else {
				A->getNode() = B;
				B->parent = A->parent;
			}
			B->right = D;
			B->color = BLACK;
			D->right = A;
			D->left = C;
			D->parent = B;
			D->color = RED;
			C->parent = D;
			C->color = BLACK;
			A->parent = D;
			A->color = BLACK;
			C->right = null;
			A->left = null;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == BLACK && getColor(son->right) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-BB-5-R]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->right;
			Node* D = C->left;
			Node* E = C->right;
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
			C->color = BLACK;
			B->parent = C;
			B->right = D;
			B->color = BLACK;
			A->parent = C;
			A->left = E;
			A->color = BLACK;
			if (D != null)
				D->parent = B;
			if (E != null)
				E->parent = A;
			return;
		}
		
		if (getColor(father) == BLACK && getColor(son) == BLACK && getColor(son->left) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-BB-5-L]\n";
#endif 
			son->left->color = BLACK;
			rotateRight(father);
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == BLACK && getColor(son->left) == BLACK && getColor(son->right) == BLACK) {
#ifdef DEBUG
			std::cout << "[CASE R-BB-6]\n";
#endif 
			son->color = RED;
			if (father == root)
				return;
			balance_next(father);
			return;
		}
	}

	void balance_left(Node* node, bool rebalance = false) {
		Node* father = node;
		Node* son = node->right;
#ifdef DEBUG
		std::cout << "Left balance\n";
		std::cout << "\nFather's color is " << (getColor(father) == BLACK ? "black" : "red") << "\n";
		std::cout << "Son's color is " << (getColor(son) == BLACK ? "black" : "red") << "\n";
		std::cout << "Left grandson's color is " << (getColor(son->left) == BLACK ? "black" : "red") << "\n";
		std::cout << "Right grandson's color is " << (getColor(son->right) == BLACK ? "black" : "red") << "\n";
#endif
		if (getColor(father) == RED && getColor(son->left) == BLACK && getColor(son->right) == BLACK) {
#ifdef DEBUG
			std::cout << "[CASE L-RB-1]\n";
#endif 
			father->color = BLACK;
			son->color = RED;
			return;
		}

		if (getColor(father) == RED && getColor(son->right) == RED) {
#ifdef DEBUG
			std::cout << "[CASE L-RB-2-R]\n";
#endif 
			rotateLeft(father);
			Node* core = father->parent;
			core->color = RED;
			core->left->color = BLACK;
			core->right->color = BLACK;
			return;
		}

		if (getColor(father) == RED && getColor(son->left) == RED) {
#ifdef DEBUG
			std::cout << "[CASE L-RB-2-L]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->left;
			Node* D = C->right;
			Node* E = C->left;
			if (A == root) {
				root = C;
				C->parent = null;
			}
			else {
				A->getNode() = C;
				C->parent = A->parent;
			}
			C->right = B;
			C->left = A;
			C->color = RED;
			B->parent = C;
			B->left = D;
			B->color = BLACK;
			A->parent = C;
			A->right = E;
			A->color = BLACK;
			if (D != null)
				D->parent = B;
			if (E != null)
				E->parent = A;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == RED && getColor(son->left->right) == BLACK && getColor(son->left->left) == BLACK) {
#ifdef DEBUG
			std::cout << "[CASE L-BR-3]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->left;
			if (A == root) {
				root = B;
				B->parent = null;
			}
			else {
				A->getNode() = B;
				B->parent = A->parent;
			}
			B->left = A;
			B->color = BLACK;
			A->parent = B;
			A->right = C;
			A->color = BLACK;
			C->parent = A;
			C->color = RED;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == RED && getColor(son->left->right) == RED) {
#ifdef DEBUG
			std::cout << "[CASE R-BR-4-R]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->left;
			Node* D = C->right;
			Node* E = C->left;
			if (A == root) {
				root = C;
				C->parent = null;
			}
			else {
				A->getNode() = C;
				C->parent = A->parent;
			}
			C->right = B;
			C->left = A;
			C->color = BLACK;
			B->parent = C;
			B->left = D;
			B->color = RED;
			A->parent = C;
			A->right = E;
			A->color = BLACK;
			D->parent = B;
			D->color = BLACK;
			if (E != null)
				E->parent = A;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == RED && getColor(son->left->left) == RED) {
#ifdef DEBUG
			std::cout << "[CASE L-BR-4-L]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->left;
			Node* D = C->left;
			if (A == root) {
				root = B;
				B->parent = null;
			}
			else {
				A->getNode() = B;
				B->parent = A->parent;
			}
			B->left = D;
			B->color = BLACK;
			D->left = A;
			D->right = C;
			D->parent = B;
			D->color = RED;
			C->parent = D;
			C->color = BLACK;
			A->parent = D;
			A->color = BLACK;
			C->left = null;
			A->right = null;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == BLACK && getColor(son->left) == RED) {
#ifdef DEBUG
			std::cout << "[CASE L-BB-5-L]\n";
#endif 
			Node* A = father;
			Node* B = son;
			Node* C = son->left;
			Node* D = C->right;
			Node* E = C->left;
			if (A == root) {
				root = C;
				C->parent = null;
			}
			else {
				A->getNode() = C;
				C->parent = A->parent;
			}
			C->right = B;
			C->left = A;
			C->color = BLACK;
			B->parent = C;
			B->left = D;
			B->color = BLACK;
			A->parent = C;
			A->right = E;
			A->color = BLACK;
			if (D != null)
				D->parent = B;
			if (E != null)
				E->parent = A;
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == BLACK && getColor(son->right) == RED) {
#ifdef DEBUG
			std::cout << "[CASE L-BB-5-R]\n";
#endif 
			son->right->color = BLACK;
			rotateLeft(father);
			return;
		}

		if (getColor(father) == BLACK && getColor(son) == BLACK && getColor(son->left) == BLACK && getColor(son->right) == BLACK) {
#ifdef DEBUG
			std::cout << "[CASE L-BB-6]\n";
#endif 
			son->color = RED;
			if (father == root)
				return;
			balance_next(father);
			return;
		}
	}

	void balance_next(Node* node) {
		if (node->parent->left == node)
			balance_left(node->parent, true);
		else
			balance_right(node->parent, true);
	}

	void delete_node(Node* node) {
		if (node == root) {
			root = null;
			return;
		}
		node->getNode() = null;
		delete node;
		return;
	}
#pragma endregion

	Node* findNearest(Node* node) {
		if (node->left != null) {
			node = node->left;
			for (; node->right != null; node = node->right);
		} else if (node->right != null) {
			node = node->right;
			for (; node->left != null; node = node->left);
		}
		return node;
	}

	void rotateLeft(Node* node) {
		Node* child = node->right;
		node->right = child->left;

		if (node->right != null)
			node->right->parent = node;

		child->parent = node->parent;

		if (node->parent == null)
			root = child;
		else 
			node->getNode() = child;

		child->left = node;
		node->parent = child;
	}

	void rotateRight(Node* node) {
		Node* child = node->left;
		node->left = child->right;

		if (node->left != null)
			node->left->parent = node;

		child->parent = node->parent;

		if (node->parent == null)
			root = child;
		else
			node->getNode() = child;

		child->right = node;
		node->parent = child;
	}

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

	int getColor(Node* node) {
		return node == null ? BLACK : node->color;
	}
};