#include "avl_tree.h"

void test_insert(avl_tree* tree)
{
	std::cout << "--------------insert test-----------------" << "\n";
	for (auto i = 0; i < 10; i++)
		tree->insert(i);
	tree->print();
	std::cout << "\n";
}

void test_remove(avl_tree* tree)
{
	std::cout << "--------------remove test-----------------" << "\n";
	std::cout << "(delete all left subtree and test if it will be balanced)" << "\n";
	std::cout << "\n";
	tree->remove(0);
	tree->remove(2);
	tree->remove(1);
	tree->print();
	std::cout << "\n";
}

int main()
{
	std::cout << "automatically balanced" << "\n";
	std::cout << "\n";
	const auto tree = new avl_tree();
	test_insert(tree);
	test_remove(tree);
	delete tree;
	return 0;
}