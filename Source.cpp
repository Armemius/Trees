#include "stdafx.h"
#include "TInclude.h"

int main() {
	RBTree tree;
	for (;;) {
		char c;
		int n;
		std::cin >> c >> n;
		system("cls");
		if (c == 'a' || c == 'A')
			tree.add(n);
		if (c == 'd' || c == 'D')
			tree.remove(n);
		if (c == 'c' || c == 'C')
			tree = RBTree();
		std::cout << std::endl;
		tree.out();
		std::cout << std::endl;
		tree.getBalance();
		std::cout << std::endl;
	}
}