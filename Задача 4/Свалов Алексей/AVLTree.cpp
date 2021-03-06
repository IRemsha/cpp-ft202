#include "pch.h"
#include <iostream>

using namespace std;

class Node
{

public:

	int key;
	int height = 1;
	Node *nodeLeft = NULL;
	Node *nodeRight = NULL;

	Node(int key)
	{
		this->key = key;
	}

};

class AVLTree {

private:
	Node* root = NULL;

	int getHeight(Node *node)
	{
		return (node) ? node->height : 0;
	}

	int getDiff(Node *node)
	{
		return (node) ? getHeight(node->nodeLeft) -
			getHeight(node->nodeRight) : 0;
	}

	int updateHeight(Node *node) {
		return max(getHeight(node->nodeLeft),
			getHeight(node->nodeRight)) + 1;
	}

	int max(int firstNodeHeight, int secondNodeHeight)
	{
		return (firstNodeHeight > secondNodeHeight) ? firstNodeHeight : secondNodeHeight;
	}

	Node* minNode(Node* node)
	{
		Node* temp = node;
		while (temp->nodeLeft)
			temp = temp->nodeLeft;
		return temp;
	}

	Node* insertToTree(Node* node, int key)
	{
		if (!node)
			return new Node(key);
		else if (key < node->key)
			node->nodeLeft = insertToTree(node->nodeLeft, key);
		else
			node->nodeRight = insertToTree(node->nodeRight, key);

		node->height = updateHeight(node);
		return rotateTree(node);
	}

	Node* deleteFromTree(Node* node, int key)
	{
		if (!node)
			return node;
		else if (key < node->key)
			node->nodeLeft = deleteFromTree(node->nodeLeft, key);
		else if (key > node->key)
			node->nodeRight = deleteFromTree(node->nodeRight, key);
		else
		{
			if (!node->nodeRight)
			{
				Node* temp = node;
				node = node->nodeLeft;
				delete(temp);
				return node;
			}
			else
			{
				Node* temp = minNode(node->nodeRight);
				node->key = temp->key;
				node->nodeRight = deleteFromTree(node->nodeRight, node->key);
			}
		}
		node->height = updateHeight(node);
		return rotateTree(node);
	}

	Node* rotateTree(Node* node) {
		int diff = getDiff(node);
		if (diff > 1) {
			if (getDiff(node->nodeLeft) >= 0) 
				return rightRotate(node);
			else 
			{
				node->nodeLeft = leftRotate(node->nodeLeft);
				return rightRotate(node);
			}
		}
		if (diff < -1)
			if (getDiff(node->nodeRight) <= 0) 
				return leftRotate(node);
			else
			{
				node->nodeRight = rightRotate(node->nodeRight);
				return leftRotate(node);
			}
		return node;
	}

	Node*leftRotate(Node *node)
	{
		Node *right = node->nodeRight;
		Node *rightLeft = right->nodeLeft;

		right->nodeLeft = node;
		node->nodeRight = rightLeft;

		node->height = updateHeight(node);
		right->height = updateHeight(right);

		return right;
	}

	Node*rightRotate(Node *node)
	{
		Node *left = node->nodeLeft;
		Node *leftRight = left->nodeRight;

		left->nodeRight = node;
		node->nodeLeft = leftRight;

		node->height = updateHeight(node);
		left->height = updateHeight(left);

		return left;
	}

	void printTree(Node *node, int level = 0)
	{
		if (node)
		{
			printTree(node->nodeRight, level + 5);
			for (int i = 0; i < level; i++) cout << "   ";
			cout << node->key << endl;
			printTree(node->nodeLeft, level + 5);
		}
	}

public:

	AVLTree(Node* root) {
		this->root = root;
	}

	void Insert(int key) {
		root = insertToTree(root, key);
	}

	void Print() {
		printTree(this->root);
		cout << "\n\n\n\n";
	}

	void Delete(int key) {
		root = deleteFromTree(root, key);
	}
};

int main()
{
	cout << "Insert elements with values from 1 to 7:" << endl;
	AVLTree* avlTree = new AVLTree(new Node(1));
	avlTree->Insert(2);
	avlTree->Insert(3);
	avlTree->Insert(4);
	avlTree->Insert(5);
	avlTree->Insert(6);
	avlTree->Insert(7);
	avlTree->Print();
	
	cout << "Delete element with value 3:" << endl;
	avlTree->Delete(3);
	avlTree->Print();
	
	cout << "Delete element with value 2:" << endl;
	avlTree->Delete(2);
	avlTree->Print();
	
	cout << "Delete element with value 4:" << endl;
	avlTree->Delete(4);
	avlTree->Print();

	cout << "Insert element with value 2:" << endl;
	avlTree->Insert(8);
	avlTree->Print();

	cout << "Insert random elements:" << endl;
	avlTree->Insert(17);
	avlTree->Insert(2);
	avlTree->Insert(500);
	avlTree->Insert(19);
	avlTree->Insert(3);
	avlTree->Insert(400);
	avlTree->Print();
	return 0;
}