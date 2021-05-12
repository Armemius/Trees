#pragma once
#include "stdafx.h"
#include "Nodes.h"

struct DScreed {
	DScreed(int x0, int y0, int x1, int y1) {
		this->x0 = x0;
		this->y0 = y0;
		this->x1 = x1;
		this->y1 = y1;
	}
	int x0 = 0, y0 = 0;
	int x1 = 0, y1 = 0;
};

struct DNode {
	DNode(int x, int y, int data, int color, int param = -1) {
		this->x = x;
		this->y = y;
		this->data = data;
		this->color = color;
		this->param = param;
	}

	int x =  0, y = 0;
	int data = 0;
	int color = 0;
	int param = -1;
};

struct DTree {
	std::vector<DScreed> screeds;
	std::vector<DNode> nodes;
};

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

	DTree getRenderKeys() {
		return this->dtree;
	}

	void reloadRenderKey() {
		dtree = DTree();
		int width = std::pow(2, getHeight(root));
		dtree.nodes.push_back(DNode(0,0, root->data, root->color, root->weight));
		if (root->left != null) {
			reloader(root->left, -width / 4, 1, width / 2);
			dtree.screeds.push_back(DScreed(0, 0, -width / 4, 1));
		}
		if (root->right != null) {
			reloader(root->right, width / 4, 1, width / 2);
			dtree.screeds.push_back(DScreed(0, 0, width / 4, 1));
		}
	}

private:
	DTree dtree;
	void reloader(Node* node, int x, int y, int width) {
		dtree.nodes.push_back(DNode(x, y, node->data, node->color, node->weight));
		if (node->left != null) {
			reloader(node->left, x - width / 4, y + 1, width / 2);
			dtree.screeds.push_back(DScreed(x, y, x - width / 4, y + 1));
		}
		if (node->right != null) {
			reloader(node->right, x + width / 4, y + 1, width / 2);
			dtree.screeds.push_back(DScreed(x, y, x + width / 4, y + 1));
		}
	}
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
