#pragma once
#include "stdafx.h"

struct Node {
public:
	Node(int);
	Node(int, Node*);

	//Returns pointer to the node
	Node*& getNode();
	bool isLeaf();
	std::string getInfo();

	int data = 0;
	int color = RED;
	int weight = -1;
	Node* left = null;
	Node* right = null;
	Node* parent = null;
};