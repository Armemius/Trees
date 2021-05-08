#pragma once
#include "ITree.h"

class RBTree : public ITree {
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
		for (Node* i = node; ; i = i->parent) {
			if (i == null)
				return;
			if (i->parent == null)
				return;
			if (i->parent->parent == null)
				return;
			add_balance(i);
		}
	}

	void add_balance(Node* node) {
		if (node == root) {
			node->color = BLACK;
#ifdef DEBUG
			std::cout << "Node is root, marking as black\n";
#endif
			return;
		}
		if (node->parent->color == BLACK) {
#ifdef DEBUG
			std::cout << "Node's father is black, no actions needed\n";
#endif
			return;
		}
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
			grandfather->right = node;
			node->parent = grandfather;
			node->right = father;
			node->left = null;
			father->parent = node;
			father->left = null;
			node = father;
		}
		if (grandfather->left != null)
		if (grandfather->left->right == node) {
#ifdef DEBUG
			std::cout << "Triangle moment on left side\n";
#endif
			grandfather->left = node;
			node->parent = grandfather;
			node->left = father;
			node->right = null;
			father->parent = node;
			father->right = null;
			node = father;
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
			A->color = BLACK;
			B->left = C;
			B->right = y;
			B->parent = A;
			if (y != null)
				y->parent = B;
			X->color = RED;
			B->color = RED;
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
			A->color = BLACK;
			B->right = C;
			B->left = y;
			B->parent = A;
			if (y != null)
				y->parent = B;
			X->color = RED;
			B->color = RED;
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

	void LeftRotation(Node* node) {

	}

	void RightRotation(Node* node) {

	}
};