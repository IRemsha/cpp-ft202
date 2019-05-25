#include "awl_tree.h"
#include <iostream>
#include <queue>

using namespace std;

void awl_tree::insert(int value)
{
	root = root ? root->insert(value) : new node(value);
}

void awl_tree::remove(int value)
{
	if (root)
		root = root->remove(value);
}

void awl_tree::print() const
{
	cout << "\n";
	if (root)
		root->print("", false, true);
}

void awl_tree::balance()
{
	if (root)
		root = root->balance();
}
