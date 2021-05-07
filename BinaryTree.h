#pragma once
#include "ITree.h"

class BinaryTree : public ITree {
	Node* t_add(int data) override {
		if (this->root == null) {
			this->root = new Node(data);
			t_size++;
			return root;
		}
		Node* tmp = root;
		for (;;) {
			if(tmp->data > data) {
				if (tmp->left == null) {
					tmp->left = new Node(data, tmp);
					t_size++;
					return tmp->left;
				}
				tmp = tmp->left;
			} else if(tmp->data < data) {
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

	Node* t_remove(int data) override {
		Node* ob = this->find(data);
		if (ob == null)
			return null;
		if (ob == root) {
			if (ob->isLeaf()) {
				root = null;
				t_size--;
				return null;
			}
			if (ob->left == null && ob->right != null) {
				root = ob->right;
				t_size--;
				delete ob;
				root->parent = null;
				return root;
			}
				
		}
		//action if node is leaf
		if (ob->isLeaf()) {
			ob->getNode() = null;
			auto ret_value = ob->parent;
			delete ob;
			t_size--;
			return ret_value;
		}
		//action if subnode is leaf
		if (ob->left != null)
			if (ob->left->isLeaf()) {
				dswap(ob, ob->left);
				ob->left->getNode() = null;
				delete ob->left;
				t_size--;
				return ob;
			}
		if (ob->right != null)
			if (ob->right->isLeaf()) {
				dswap(ob, ob->right);
				ob->right->getNode() = null;
				delete ob->right;
				t_size--;
				return ob;
			}
		//action if subnode is not leaf
		if (ob->left != null) {
			Node* tmp = ob->left;
			if (tmp->right == null) {
				dswap(ob, tmp);
				tmp->left->parent = ob;
				ob->left = tmp->left;
				delete tmp;
				t_size--;
				return ob;
			} else {
				for (;tmp->right != null; tmp = tmp->right);
				dswap(ob, tmp);
				if (tmp->left == null) {
					tmp->getNode() = null;
					Node* ret_value = tmp->parent;
					delete tmp;
					t_size--;
					return ret_value;
				} else {
					tmp->left->parent = tmp->parent;
					tmp->getNode() = tmp->left;
					Node* ret_value = tmp->parent;
					delete tmp;
					t_size--;
					return ret_value;
				}
			}
		} else if (ob->right != null) {
			ob->right->parent = ob->parent;
			ob->getNode() = ob->right;
			Node* ret_value = ob->parent;
			delete ob;
			t_size--;
			return ret_value;
		}
		return null;
	}

	void add_action(Node* node) override {
		node->color = LIGHT_BLUE;
	}
	
	void remove_action(Node* node) override {}
};