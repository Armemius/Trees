#include "stdafx.h"
#include "TInclude.h"
#include "ITree.h"

class TreesHandler {
public:
	void add(int data) {
		try {
			binold = bintree.getRenderKeys();
			rbold = rbtree.getRenderKeys();
			avlold = avltree.getRenderKeys();
			treapold = treap.getRenderKeys();
			splayold = splaytree.getRenderKeys();
			bintree.add(data);
			rbtree.add(data);
			avltree.add(data);
			treap.add(data);
			splaytree.add(data);
			binnew = bintree.getRenderKeys();
			rbnew = rbtree.getRenderKeys();
			avlnew = avltree.getRenderKeys();
			treapnew = treap.getRenderKeys();
			splaynew = splaytree.getRenderKeys();
		}
		catch (std::exception) {
			std::cout << "Something went wrong(\n";
		}
	}

	void remove(int data) {
		try {
			binold = bintree.getRenderKeys();
			rbold = rbtree.getRenderKeys();
			avlold = avltree.getRenderKeys();
			treapold = treap.getRenderKeys();
			splayold = splaytree.getRenderKeys();
			bintree.remove(data);
			rbtree.remove(data);
			avltree.remove(data);
			treap.remove(data);
			splaytree.remove(data);
			binnew = bintree.getRenderKeys();
			rbnew = rbtree.getRenderKeys();
			avlnew = avltree.getRenderKeys();
			treapnew = treap.getRenderKeys();
			splaynew = splaytree.getRenderKeys();
		}
		catch (std::exception) {
			std::cout << "Something went wrong(\n";
		}
	}



private:
	BinaryTree bintree;
	DTree binnew, binold;
	RBTree rbtree;
	DTree rbnew, rbold;
	AVLTree avltree;
	DTree avlnew, avlold;
	Treap treap;
	DTree treapnew, treapold;
	SplayTree splaytree;
	DTree splaynew, splayold;
};