#include "stdafx.h"
#include "TInclude.h"

int main() {
	AVLTree tree;
	std::vector<int> insert{5, 15, 10, 50, 80, 150, 190, 140, 200, 230};
	tree.add(insert);

	tree.out();
}