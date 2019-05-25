#include <iostream>
#include "avl_tree.h"

using namespace std;

void print_header(const string& header)
{
	cout << "\n------===| " + header + " |===------\n";
}

void show_insert(avl_tree& tree)
{
	print_header("inserting 0 to 9");

	for (auto i = 0; i < 10; i++)
		tree.insert(i);
	tree.print();

	print_header("inserting done");
}

void show_remove(avl_tree & tree)
{
	print_header("removing 3, 4, 5, 9, 0");

	tree.remove(3);
	tree.remove(4);
	tree.remove(5);
	tree.remove(9);
	tree.remove(0);
	tree.print();

	print_header("removing done");
}

void show_balance()
{
	print_header("info about balancing");
	cout << "\nBalancing is done automatically, when needed\n";
	cout << "but can be called manually, if needed, using tree.balance();\n";
	print_header("info about balancing finished");
}

int main()
{
	auto tree = avl_tree();

	show_balance();
	cout << "\n\n\n\n";
	show_insert(tree);
	cout << "\n\n\n\n";
	show_remove(tree);
}
