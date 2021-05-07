#pragma once
#include "ITree.h"

class AVLTree : public ITree {
	Node* t_add(int data) override {
		if (this->root == null) {
			this->root = new Node(data);
			t_size++;
			return root;
		}
		Node* tmp = root;
		for (;;) {
			if (tmp->data > data) {
				if (tmp->left == null) {
					tmp->left = new Node(data, tmp);
					t_size++;
					return tmp->left;
				}
				tmp = tmp->left;
			}
			else if (tmp->data < data) {
				if (tmp->right == null) {
					tmp->right = new Node(data, tmp);
					t_size++;
					return tmp->right;
				}
				tmp = tmp->right;
			}
			else
				return null;
		}
	}

	Node* t_remove(int field) override {
		return null;
	}

	void add_action(Node* node) override {
		node->color = GREEN;
		for (Node* tmp = this->root; tmp != node;) {
			tmp->weight = getHeight(tmp->right) - getHeight(tmp->left);
			if (tmp->data > node->data) {
				tmp = tmp->left;
			} else if (tmp->data < node->data) {
				tmp = tmp->right;
			}
		}
		for (Node* tmp = node; tmp != null; tmp = tmp->parent) {
			if (std::abs(tmp->weight) >= 2)
				balance(tmp);
		}
	}

	void remove_action(Node* node) override {

	}

	void balance(Node* start) {
		//Small left rotation
		if (start->right != null) {
			if (getHeight(start->right) - getHeight(start->left) == 2 && getHeight(start->right->left) <= getHeight(start->right->right)) {
				SLRotation(start);
				return;
			}
		}
		//Big left rotation
		if (start->right != null) {
			if (start->right->left != null) {
				if (getHeight(start->right) - getHeight(start->left) == 2 && getHeight(start->right->left) > getHeight(start->right->right)) {
					BLRotation(start);
					return;
				}
			}
		}
		//Small right rotation
		if (start->left != null) {
			if (getHeight(start->left) - getHeight(start->right) == 2 && getHeight(start->left->right) <= getHeight(start->left->left)) {
				SRRotation(start);
				return;
			}
		}
		//Big right rotation
		if (start->left != null) {
			if (start->left->right != null) {
				if (getHeight(start->left) - getHeight(start->right) == 2 && getHeight(start->left->right) > getHeight(start->left->left)) {
					BRRotation(start);
					return;
				}
			}
		}
	}

	void SLRotation(Node* start) {
#ifdef DEBUG
		std::cout << "Small Left Rotation " << start->getInfo() << "\n";
#endif
		Node* a = start;
		Node* b = start->right;
		Node* L = start->left;
		Node* C = start->right->left;
		Node* R = start->right->right;
		if (start->parent == null) {
			root = b;
			b->parent = null;
		} else {
			a->getNode() = b;
			b->parent = a->parent;
		}
		b->left = a;
		b->right = R;
		a->left = L;
		a->right = C;
		a->parent = b;
		if (L != null)
			L->parent = a;
		if (C != null)
			C->parent = a;
		if (R != null)
			R->parent = b;
		a->weight = getHeight(a->right) - getHeight(a->left);
		b->weight = getHeight(b->right) - getHeight(b->left);
		for (Node* i = b; i != null; i = i->parent)
			i->weight = getHeight(i->right) - getHeight(i->left);
	}

	void BLRotation(Node* start) {
#ifdef DEBUG
		std::cout << "Big Left Rotation " << start->getInfo() << "\n";
#endif
		Node* a = start;
		Node* b = start->right;
		Node* c = start->right->left;
		Node* L = start->left;
		Node* M = start->right->left->left;
		Node* N = start->right->left->right;
		Node* R = start->right->right;
		if (start->parent == null) {
			root = c;
			c->parent = null;
		} else {
			a->getNode() = c;
			c->parent = a->parent;
		}
		c->left = a;
		c->right = b;
		a->parent = c;
		a->left = L;
		a->right = M;
		b->parent = c;
		b->left = N;
		b->right = R;
		if (L != null)
			L->parent = a;
		if (M != null)
			M->parent = a;
		if (N != null)
			N->parent = b;
		if (R != null)
			R->parent = b;
		a->weight = getHeight(a->right) - getHeight(a->left);
		b->weight = getHeight(b->right) - getHeight(b->left);
		c->weight = getHeight(c->right) - getHeight(c->left);
		for (Node* i = c; i != null; i = i->parent)
			i->weight = getHeight(i->right) - getHeight(i->left);
	}

	void SRRotation(Node* start) {
#ifdef DEBUG
		std::cout << "Small Right Rotation " << start->getInfo() << "\n";
#endif
		Node* a = start;
		Node* b = start->left;
		Node* L = start->left->left;
		Node* C = start->left->right;
		Node* R = start->right;
		if (start->parent == null) {
			root = b;
			b->parent = null;
		}
		else {
			a->getNode() = b;
			b->parent = a->parent;
		}
		b->left = L;
		b->right = a;
		a->left = C;
		a->right = R;
		a->parent = b;
		if (L != null)
			L->parent = b;
		if (C != null)
			C->parent = a;
		if (R != null)
			R->parent = a;
		a->weight = getHeight(a->right) - getHeight(a->left);
		b->weight = getHeight(b->right) - getHeight(b->left);
		for (Node* i = b; i != null; i = i->parent)
			i->weight = getHeight(i->right) - getHeight(i->left);
	}

	void BRRotation(Node* start) {
#ifdef DEBUG
		std::cout << "Big Right Rotation " << start->getInfo() << "\n";
#endif
		Node* a = start;
		Node* b = start->left;
		Node* c = start->left->right;
		Node* L = start->left->left;
		Node* M = start->left->right->left;
		Node* N = start->left->right->right;
		Node* R = start->right;
		if (start->parent == null) {
			root = c;
			c->parent = null;
		}
		else {
			a->getNode() = c;
			c->parent = a->parent;
		}
		c->left = b;
		c->right = a;
		b->left = L;
		b->right = M;
		b->parent = c;
		a->left = N;
		a->right = R;
		a->parent = c;
		if (L != null)
			L->parent = b;
		if (M != null)
			M->parent = b;
		if (N != null)
			N->parent = a;
		if (R != null)
			R->parent = a;
		a->weight = getHeight(a->right) - getHeight(a->left);
		b->weight = getHeight(b->right) - getHeight(b->left);
		c->weight = getHeight(c->right) - getHeight(c->left);
		for (Node* i = c; i != null; i = i->parent)
			i->weight = getHeight(i->right) - getHeight(i->left);
	}
};