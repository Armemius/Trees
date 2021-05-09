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

	Node* t_remove(int data) override {
		return null;
	}

	void remove_action(Node* node) override {

	}
};