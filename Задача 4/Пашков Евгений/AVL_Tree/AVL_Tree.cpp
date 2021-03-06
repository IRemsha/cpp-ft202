#include "stdafx.h"
#include "algorithm"
#include "iostream"
#include "cmath"
#include "Windows.h"

using namespace std;

class AVL_Tree
{
	struct Node
	{
		int Value;
		int Height;
		Node* Left;
		Node* Right;
		Node(int value) : Value(value) 
		{ 
			Left = Right = nullptr;
			Height = 1; 
		}
	};

	int getHeight(Node* node)
	{
		if (node)
			return node->Height;
		return 0;
	}

	int getBalanceFactor(Node* node)
	{
		return getHeight(node->Right) - getHeight(node->Left);
	}

	void fixHeight(Node* node)
	{
		int heightLeft = getHeight(node->Left);
		int heightRight = getHeight(node->Right);		
		node->Height = max(heightLeft, heightRight) + 1;
	}

	Node* rotateLeft(Node* q) // левый поворот вокруг q
	{
		Node* p = q->Right;
		q->Right = p->Left;
		p->Left = q;
		fixHeight(q);
		fixHeight(p);
		return p;
	}

	Node* rotateRight(Node* p) // правый поворот вокруг p
	{
		Node* q = p->Left;
		p->Left = q->Right;
		q->Right = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node* balanceTree(Node* node) // балансировка узла node
	{
		fixHeight(node);
		int balanceFactor = getBalanceFactor(node);
		if (balanceFactor == -2)
		{
			if (getBalanceFactor(node->Left) > 0)
				node->Left = rotateLeft(node->Left);
			return rotateRight(node);
		}
		else if (balanceFactor == 2)
		{
			if (getBalanceFactor(node->Right) < 0)
				node->Right = rotateRight(node->Right);
			return rotateLeft(node);
		}
		return node; // балансировка не нужна
	}

	Node* insertValue(Node* node, int valueToInsert) // вставка ключа valueToInsert в дерево с корнем node
	{
		if (!node)
			return new Node(valueToInsert);
		if (valueToInsert >= node->Value)
			node->Right = insertValue(node->Right, valueToInsert);
		else
			node->Left = insertValue(node->Left, valueToInsert);
		return balanceTree(node);
	}

	Node* findMin(Node* node) // поиск узла с минимальным ключом в дереве node
	{
		Node* left = node->Left;
		if (!left)
			return node;
		return findMin(left);
	}

	Node* removeMin(Node* node) // удаление узла с минимальным ключом из дерева с корнем node
	{
		if (node->Left == 0)
			return node->Right;
		node->Left = removeMin(node->Left);
		return balanceTree(node);
	}

	Node* removeValue(Node* node, int valueToRemove) // удаление значения valueToRemove из дерева с корнем node
	{
		if (!node) 
			return 0;

		int currentValue = node->Value;
		if (valueToRemove > currentValue)
		{
			node->Right = removeValue(node->Right, valueToRemove);
		}
		else if (valueToRemove < currentValue)
		{
			node->Left = removeValue(node->Left, valueToRemove);
		}
		else
		{
			Node* leftNode = node->Left;
			Node* rightNode = node->Right;
			delete node;
			if (!rightNode) 
				return leftNode;
			Node* minNode = findMin(rightNode);
			minNode->Right = removeMin(rightNode);
			minNode->Left = leftNode;
			return balanceTree(minNode);
		}
		return balanceTree(node);
	}
	
	void printTree(Node* node, int level) // печать дерева с корнем node, дерево повернуто на 90 градусов влево
	{
		if (!node)
			return;
		printTree(node->Right, level + 4);
		for (int i = 0; i < level; i++)
			cout << "  ";
		cout << node->Value << endl;
		printTree(node->Left, level + 4);
	}

public:
	Node* Root;

	AVL_Tree() {}
	
	AVL_Tree(int value)
	{
		Root = new Node(value);
	}

	void balance()
	{
		Root = balanceTree(Root);
	}

	void insert(int valueToInsert)
	{
		Root = insertValue(Root, valueToInsert);
	}

	void remove(int valueToRemove)
	{
		Root = removeValue(Root, valueToRemove);
	}

	void print()
	{
		cout << endl;
		cout << "********************" << endl;
		printTree(Root, 0);
		cout << "********************" << endl;
		cout << endl;
	}
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	AVL_Tree* tree = new AVL_Tree();
	cout << "Добавляем в дерево элементы с 1 по 5" << endl;
	for (int i = 1; i <= 5; i++)
	{
		tree->insert(i);
		tree->print();
	}
	cout << "Добавляем в дерево элементы с 6 по 10" << endl;
	for (int i = 6; i <= 10; i++)
		tree->insert(i);
	tree->print();
	cout << "Удаляем элемент 8" << endl;
	tree->remove(8);
	tree->print();
	cout << "Удаляем элемент 4" << endl;
	tree->remove(4);
	tree->print();
	cout << "Добавляем элемент 8" << endl;
	tree->insert(8);
	tree->print();
}