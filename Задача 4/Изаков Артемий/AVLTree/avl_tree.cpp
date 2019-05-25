#include "avl_tree.h"
#include <iostream>
#include <queue>

using namespace std;

void avl_tree::insert(int value)
{
	root = root ? root->insert(value) : new node(value);
}

void avl_tree::remove(int value)
{
	if (root)
		root = root->remove(value);
}

void avl_tree::print() const
{
	cout << "\n";
	if (root)
		root->print("", false, true);
}

void avl_tree::balance()
{
	if (root)
		root = root->balance();
}
