#include "pch.h"
#include <iostream>
using namespace std;

struct Node
{
	int value;
	int height;
	Node* left;
	Node* right;

	Node(int value) 
	{
		this->value = value;
		left = right = 0; 
		height = 1; 
	}
};

class AVLTree
{

	Node* root;

public:
	AVLTree()
	{
		root = 0;
	}

	void insert(int value)
	{
		root = insert(root, value);
	}

	void remove(int value)
	{
		root = remove(root, value);
	}

	void print() {
		print(root, 0);
		printf("=================\n");
	}

private:
	int height(Node* node)
	{
		if (node)
			return node->height;
		return 0;
	}

	int balanceF(Node* node)
	{
		return height(node->right) - height(node->left);
	}

	void fixHeight(Node* node)
	{
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);
		node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	Node* rightRotate(Node* node)
	{
		Node* leftNode = node->left;
		node->left = leftNode->right;
		leftNode->right = node;
		fixHeight(node);
		fixHeight(leftNode);
		return leftNode;
	}

	Node* leftRotate(Node* node)
	{
		Node* rightNode = node->right;
		node->right = rightNode->left;
		rightNode->left = node;
		fixHeight(node);
		fixHeight(rightNode);
		return rightNode;
	}

	Node* balance(Node* node)
	{
		fixHeight(node);
		if (balanceF(node) == 2)
		{
			if (balanceF(node->right) < 0)
				node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		if (balanceF(node) == -2)
		{
			if (balanceF(node->left) > 0)
				node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		return node;
	}

	Node* insert(Node* node, int value)
	{
		if (!node) return new Node(value);
		if (value < node->value)
			node->left = insert(node->left, value);
		else
			node->right = insert(node->right, value);
		return balance(node);
	}

	Node* findMin(Node* node)
	{
		return node->left ? findMin(node->left) : node;
	}

	Node* removeMin(Node* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = removeMin(node->left);
		return balance(node);
	}

	Node* remove(Node* node, int value)
	{
		if (!node)
			return 0;
		if (value < node->value)
			node->left = remove(node->left, value);
		else if (value > node->value)
			node->right = remove(node->right, value);
		else
		{
			Node* leftNode = node->left;
			Node* rightNode = node->right;
			delete node;
			if (!rightNode) return leftNode;
			Node* min = findMin(rightNode);
			min->right = removeMin(rightNode);
			min->left = leftNode;
			return balance(min);
		}
		return balance(node);
	}

	void print(Node* node, int level)
	{
		if (node)
		{
			print(node->right, level + 1);
			for (int i = 0; i < level; i++) cout << "   ";
			cout << node->value << endl;
			print(node->left, level + 1);
		}
	}
};

int main()
{
	AVLTree tree = AVLTree();
	tree.insert(1);
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.print();

	tree.remove(5);
	tree.print();

	tree.remove(1);
	tree.print();

	for (int i = 0; i < 7; i++)
		tree.insert(i);
	tree.print();

	for (int i = 0; i < 7; i++)
		tree.remove(i);
	tree.print();
}
