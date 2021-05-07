#pragma once
#include "stdafx.h"
#include "Nodes.h"

void dswap(Node*& first, Node*& second) {
	int data = first->data;
	first->data = second->data;
	second->data = data;
	return;
}

class ITree {
public:
	void add(std::vector<int> data) {
		for (int i : data) {
			this->add(i);
		}
		return;
	}

	void add(int data) {
		Node* tmp = t_add(data);
		if (tmp != null)
			add_action(tmp);
		return;
	}

	void remove(int data) {
		Node* tmp = t_remove(data);
		if (tmp != null)
			remove_action(tmp);
		return;
	}

	void out() {
		out(root);
		return;
	}

	int size() {
		return this->t_size;
	}

private:
	void out(Node* node) {
		if (node == null) return;
		out(node->left);
		std::cout << node->getInfo() << "\n";
		out(node->right);
	}
protected:
	virtual Node* t_add(int) = null;
	virtual Node* t_remove(int) = null;
	virtual void add_action(Node*) = null;
	virtual void remove_action(Node*) = null;
	Node* root = null;
	int t_size = 0;
	Node* find(int data) {
		if (this->root == null)
			return null;
		Node* tmp = root;
		for (;;) {
			if (tmp->data > data) {
				if (tmp->left == null) {
					return null;
				}
				tmp = tmp->left;
			}
			else if (tmp->data < data) {
				if (tmp->right == null) {
					return null;
				}
				tmp = tmp->right;
			}
			else
				return tmp;
		}
	}

	int getHeight(Node* node, int height = 0) {
		if (node == null)
			return height;
		return max(getHeight(node->left, height + 1), getHeight(node->right, height + 1));
	}
};
