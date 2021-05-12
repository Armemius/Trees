#pragma once
#include "ITree.h"

class Treap : public ITree {
	int seed = 666;

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
		node->color = WHITE;
		seed = std::cos(seed) * rand() + 228;
		srand(seed);
		node->weight = 500 + (rand() % 500) * cos(seed);
		balance(node);
	}

	void balance(Node* node) {
		if (node == root)
			return;
		if (node->weight >= node->parent->weight) {
			if (node->parent->right == node)
				rotateLeft(node->parent);
			else
				rotateRight(node->parent);
			balance(node);
		}
	}

	Node* t_remove(int data) override {
		Node* ob = this->find(data);
		if (ob == null)
			return null;
		if (ob->isLeaf()) {
			if (ob == root) {
				root = null;
				return null;
			}
			ob->getNode() = null;
			delete ob;
			return null;
		}
		r_remove(ob);
		return null;
	}

	void r_remove(Node* node) {
		if (node->isLeaf()) {
			node->getNode() = null;
			delete node;
			return;
		}
		Node* tmp = findNearest(node);
		dswap(node, tmp);
		r_remove(tmp);
	}

	Node* findNearest(Node* node) {
		if (node->left != null) {
			node = node->left;
			for (; node->right != null; node = node->right);
		}
		else if (node->right != null) {
			node = node->right;
			for (; node->left != null; node = node->left);
		}
		return node;
	}

	void rotateLeft(Node* node) {
		Node* X = node;
		Node* Y = node->right;
		Node* b = Y->left;
		if (X == root) {
			root = Y;
			Y->parent = null;
		} else {
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

	void rotateRight(Node* node) {
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

	void remove_action(Node* node) override {
		//Ne treba
	}

};