#include "Nodes.h"

Node::Node(int data) {
	this->data = data;
}

Node::Node(int data, Node* parent) {
	this->data = data;
	this->parent = parent;
}

Node*& Node::getNode() {
	if (this->parent == null)
		throw std::exception("No parent detected");
	if (this->parent->left == this)
		return this->parent->left;
	if (this->parent->right == this)
		return this->parent->right;
	std::exception("Amogus moment");
}

bool Node::isLeaf() {
	return this->left == null && this->right == null;
}


std::string Node::getInfo() {
	if (this == null)
		return "[NULL]";
	std::string res = "";
	res += "[Data: ";
	res += std::to_string(this->data) + "; ";

	res += "Parent:";
	if (this->parent == null)
		res += "N/A; ";
	else
		res += std::to_string(this->parent->data) + "; ";

	res += "Left:";
	if (this->left == null)
		res += "N/A; ";
	else
		res += std::to_string(this->left->data) + "; ";

	res += "Right:";
	if (this->right == null)
		res += "N/A; ";
	else
		res += std::to_string(this->right->data) + "; ";

	res += "Color: ";
	res += std::to_string(this->color) + "; ";

	res += "Weight: ";
	res += std::to_string(this->weight);

	res += "]";
	return res;
}