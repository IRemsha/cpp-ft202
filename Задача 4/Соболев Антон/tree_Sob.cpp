#include "pch.h"
#include <iostream>
#include <iomanip>

using namespace std;

struct TreeNode
{
	int value;
	TreeNode* left;
	TreeNode* right;
	int height;

	TreeNode(int value)
	{
		this->value = value;
		left = 0;
		right = 0;
		height = 1;
	}
};

class AVL_tree
{
private:
	unsigned char get_height(TreeNode* node)
	{
		return node ? node->height : 0;
	}

	void upd_height(TreeNode* node) {
		auto left = get_height(node->left);
		auto right = get_height(node->right);
		node->height = (left > right ? left : right) + 1;
	}


	int get_balance_factor(TreeNode* node)
	{
		return get_height(node->right) - get_height(node->left);
	}


	TreeNode* rotate_right(TreeNode* node)
	{
		TreeNode* left = node->left;
		node->left = left->right;
		left->right = node;
		upd_height(node);
		upd_height(left);
		return left;
	}

	TreeNode* rotate_left(TreeNode* node)
	{
		TreeNode* right = node->right;
		node->right = right->left;
		right->left = node;
		upd_height(node);
		upd_height(right);
		return right;
	}

	TreeNode* balance(TreeNode* to_balance)
	{
		upd_height(to_balance);
		if (get_balance_factor(to_balance) == 2)
		{
			if (get_balance_factor(to_balance->right) < 0)
				to_balance->right = rotate_right(to_balance->right);
			return rotate_left(to_balance);
		}
		if (get_balance_factor(to_balance) == -2)
		{
			if (get_balance_factor(to_balance->left) > 0)
				to_balance->left = rotate_left(to_balance->left);
			return rotate_right(to_balance);
		}
		return to_balance;
	}

	TreeNode* insert(TreeNode* node, int val)
	{
		if (!node) return new TreeNode(val);
		if (val < node->value)
			node->left = insert(node->left, val);
		else
			node->right = insert(node->right, val);
		return balance(node);
	}

	TreeNode* find_min(TreeNode* node)
	{
		return node->left ? find_min(node->left) : node;
	}

	TreeNode* remove_min(TreeNode* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = remove_min(node->left);
		return balance(node);
	}

	void print_from_node(TreeNode *p, int n) {
		if (p) {
			print_from_node(p->left, n + 5);
			for (auto i = 0; i < n; i++) {
				printf(" ");
			}
			printf("%d\n", p->value);
			print_from_node(p->right, n + 5);
		}
	}
	TreeNode* remove(TreeNode* node, int val)
	{
		if (!node) return 0;
		if (val < node->value)
			node->left = remove(node->left, val);
		else if (val > node->value)
			node->right = remove(node->right, val);
		else
		{
			TreeNode* left = node->left;
			TreeNode* right = node->right;
			delete node;
			if (!right)
				return left;
			TreeNode* min = find_min(right);
			min->right = remove_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
	}
public:
	TreeNode* root;

	void insert(int value)
	{
		root = insert(root, value);
	}

	void remove(int value)
	{
		root = remove(root, value);
	}

	void balance()
	{
		root = balance(root);
	}

	void print()
	{
		print_from_node(root,0);
		cout << "____________________________________" << endl;
	}
};

int main() {
	auto tree = new AVL_tree();
	for (int i = 2; i < 15; i++)
		tree->insert(i);
	tree->print();

	cout << " - [7]" << endl;
	tree->remove(7);
	tree->print();

	cout << " + [16]" << endl;
	tree->insert(16);
	tree->print();

	cout << " + [7]" << endl;
	tree->insert(7);
	tree->print();

	cout << " - [2]" << endl;
	tree->remove(2);
	tree->print();

	cout << " + [0]" << endl;
	tree->insert(0);
	tree->print();
}