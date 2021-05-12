#pragma once
#include "ITree.h"

class SplayTree : public ITree {
	Node* t_add(int data) override {
		if (this->root == null) {
			this->root = new Node(data);
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
		node->color = VIOLET;
		splay(node);
	}

	void splay(Node* node) {
		if (node == root)
			return;
			if (node->parent == root) {
				if (node->parent->left == node)
					zig_right(node);
				else
					zig_left(node);
			} else {
				if (node->parent->parent->left != null)
				if (node->parent->parent->left->left == node) {
					zigzig_left(node);
					splay(node);
					return;
				}  
				if (node->parent->parent->right != null)
				if (node->parent->parent->right->right == node) {
					zigzig_right(node);
					splay(node);
					return;
				}
				if (node->parent->parent->left != null)
				if (node->parent->parent->left->right == node) {
					zigzag_right(node);
					splay(node);
					return;
				} 
				if (node->parent->parent->right != null)
				if (node->parent->parent->right->left == node) {
					zigzag_left(node);
					splay(node);
					return;
				}
			}
			
	}

#pragma region OPERATIONS
	void zig_left(Node* node) {
#ifdef DEBUG
		std::cout << "Zig left\n";
#endif
		rotateRight(node->parent);
	}

	void zig_right(Node* node) {
#ifdef DEBUG
		std::cout << "Zig right\n";
#endif
		rotateLeft(node->parent);
	}

	void zigzig_right(Node* node) {
#ifdef DEBUG
		std::cout << "Zigzig left\n";
#endif
		rotateRight(node->parent->parent);
		rotateRight(node->parent);
	}

	void zigzig_left(Node* node) {
#ifdef DEBUG
		std::cout << "Zigzig right\n";
#endif
		rotateLeft(node->parent->parent);
		rotateLeft(node->parent);
	}

	void zigzag_left(Node* node) {
#ifdef DEBUG
		std::cout << "Zigzag left\n";
#endif
		rotateLeft(node->parent);
		rotateRight(node->parent);
	}

	void zigzag_right(Node* node) {
#ifdef DEBUG
		std::cout << "Zigzag right\n";
#endif
		rotateRight(node->parent);
		rotateLeft(node->parent);
	}

	void rotateRight(Node* node) {
		Node* X = node;
		Node* Y = node->right;
		Node* b = Y->left;
		if (X == root) {
			root = Y;
			Y->parent = null;
		}
		else {
			X->getNode() = Y;
			Y->parent = X->parent;
		}
		Y->left = X;
		X->parent = Y;
		X->right = b;
		if (b != null)
			b->parent = X;
		return;
	}

	void rotateLeft(Node* node) {
		Node* X = node;
		Node* Y = node->left;
		Node* b = Y->right;
		if (X == root) {
			root = Y;
			Y->parent = null;
		}
		else {
			X->getNode() = Y;
			Y->parent = X->parent;
		}
		Y->right = X;
		X->parent = Y;
		X->left = b;
		if (b != null)
			b->parent = X;
		return;
	}
#pragma endregion

	Node* t_remove(int data) override {
		Node* ob = this->find(data);
		if (ob == null)
			return null;
		splay(ob);
		return ob;
	}

	void remove_action(Node* node) override {
		if (node->isLeaf()) {
			root = null;
			return;
		}
		root = null;
		Node* tree1 = node->left;
		Node* tree2 = node->right;
		if (tree1 == null) {
			root = tree2;
			tree2->parent = null;
			Node* tmp = root;
			for (; tmp->left != null; tmp = tmp->left);
			splay(tmp);
			return;
		}
		if (tree2 == null) {
			root = tree1;
			tree1->parent = null;
			Node* tmp = root;
			for (; tmp->right != null; tmp = tmp->right);
			splay(tmp);
			return;
		}
#ifdef DEBUG
		std::cout << "Merging...\n";
#endif 
		root = tree1;
		tree1->parent = null;
		Node* tmp = root;
		for (; tmp->right != null; tmp = tmp->right);
		splay(tmp);
		tree1->right = tree2;
		tree2->parent = root;
		return;
	}
};

/*
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
*/