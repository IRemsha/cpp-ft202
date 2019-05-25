#include "pch.h"
#include <iostream>

using namespace std;


struct Node
{
	int value;
	unsigned char height;
	Node* left;
	Node* right;

	Node(int n) {
		value = n;
		left = nullptr;
		right = nullptr;
		height = 1;
	}
};

class AVLTree
{
private:
	Node* root = nullptr;

	unsigned char get_height(Node* node)
	{
		return node ? node->height : 0;
	}

	int get_bfactor(Node* node)
	{
		return get_height(node->right) - get_height(node->left);
	}

	void height(Node* node)
	{
		unsigned char left_h = get_height(node->left);
		unsigned char right_h = get_height(node->right);
		node->height = (left_h > right_h ? left_h : right_h) + 1;
	}

	Node* _insert(Node* node, int key)
	{
		if (!node) return new Node(key);
		if (key < node->value)
			node->left = _insert(node->left, key);
		else
			node->right = _insert(node->right, key);
		return balance(node);
	}

	Node* balance(Node* node)
	{
		height(node);
		if (get_bfactor(node) == 2)
		{
			if (get_bfactor(node->right) < 0)
				node->right = rotate_right(node->right);
			return rotate_left(node);
		}
		if (get_bfactor(node) == -2)
		{
			if (get_bfactor(node->left) > 0)
				node->left = rotate_left(node->left);
			return rotate_right(node);
		}
		return node;
	}

	Node* rotate_right(Node* node)
	{
		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		height(node);
		height(left);
		return left;
	}

	Node* rotate_left(Node* node)
	{
		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		height(node);
		height(right);
		return right;
	}

	Node* _remove(Node* node, int key)
	{
		if (!node)
			return 0;
		if (key < node->value)
			node->left = _remove(node->left, key);
		else if (key > node->value)
			node->right = _remove(node->right, key);
		else
		{
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if (!right)
				return left;
			Node* min = min_key(right);
			min->right = remove_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
	}

	Node* min_key(Node* node)
	{
		return node->left ? min_key(node->left) : node;
	}

	Node* remove_min(Node* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = remove_min(node->left);
		return balance(node);
	}

	void _print(Node *root, int space)
	{
		if (root == nullptr)
			return;

		space += 8;
		_print(root->right, space);
		cout << endl;
		for (int i = 10; i < space; i++)
			cout << " ";
		cout << root->value << "\n";
		_print(root->left, space);
	}

public:
	void insert(int key) {
		root = _insert(root, key);
	}

	void balance() {
		root = balance(root);
	}

	void remove(int key) {
		root = _remove(root, key);
	}

	void print()
	{
		_print(root, 0);
	}
};

int main() {
	auto tree = new AVLTree();
	cout << "FILLING" << endl;
	for (int i = 0; i <10; i++)
		tree->insert(i);
	tree->print();

	cout << "REMOVING 7" << endl;
	tree->remove(7);
	tree->print();
}