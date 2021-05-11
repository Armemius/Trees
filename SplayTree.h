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

	}


	Node* t_remove(int data) override {

	}

	void remove_action(Node* node) override {

	}
};
