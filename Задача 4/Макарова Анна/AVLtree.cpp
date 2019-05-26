#include "pch.h"
#include <iostream>
#include <string>

class node {
public:
	int value;
	node* right;
	node* left;
	int height;

	node(int value) {
		this->value = value;
		left = 0;
		right = 0;
		height = 1;
	}
};

class AVLtree {

	static int height(node* node) {
		return node ? node->height : 0;
	}

	static int balanceFactor(node* node) {
		return height(node->right) - height(node->left);
	}

	static void fixHeight(node* node) {
		int hl = height(node->left);
		int hr = height(node->right);
		node->height = (hl > hr ? hl : hr) + 1;
	}

	static node* rotateRight(node* p)
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	static node* rotateLeft(node* q)
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixHeight(q);
		fixHeight(p);
		return p;
	}

	static node* findmin(node* p)
	{
		return p->left ? findmin(p->left) : p;
	}

	static node* removemin(node* p)
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

public:
	static node* insert(node* r, int newValue)
	{
		if (!r)
			return new node(newValue);
		if (newValue < r->value)
			r->left = insert(r->left, newValue);
		else
			r->right = insert(r->right, newValue);
		return balance(r);
	}

	static node* remove(node* p, int k)
	{
		if (!p)
			return 0;
		if (k < p->value)
			p->left = remove(p->left, k);
		else if (k > p->value)
			p->right = remove(p->right, k);
		else
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	static node* balance(node* p)
	{
		fixHeight(p);
		if (balanceFactor(p) == 2)
		{
			if (balanceFactor(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if (balanceFactor(p) == -2)
		{
			if (balanceFactor(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p;
	}

	static void print(node* p, int shift=0) {
		auto indent = std::string(shift, '\t');
		std::cout << p->value << " (subtree height: " << p->height << ") \n";
		if (p->left) {
			std::cout << indent << "left: ";
			print(p->left, shift + 1);
			//std::cout << "\n";
		}
		if (p->right) {
			std::cout << indent << "right: ";
			print(p->right, shift + 1);
			std::cout << "\n";
		}
	}
};

void test1() {
	std::cout << "---------------------------\n";
	std::cout << "| Tree of many nodes test |\n";
	std::cout << "---------------------------\n";
	node* root = new node(1);
	for (int i = 2; i < 30; i++) {
		root = AVLtree::insert(root, i);
	}
	AVLtree::print(root);
}

void test2() {
	std::cout << "--------------------------------\n";
	std::cout << "| Remove and insert nodes test |\n";
	std::cout << "--------------------------------\n";
	node* root = new node(1);
	for (int i = 2; i < 7; i++) {
		root = AVLtree::insert(root, i);
	}
	AVLtree::print(root);
	
	root = AVLtree::remove(root, 2);
	root = AVLtree::remove(root, 5);
	std::cout << "   [ Tree after removing nodes 2, 5 ]\n\n";
	AVLtree::print(root);

	for (int i = 1; i < 4; i++) {
		root = AVLtree::insert(root, i * 10);
	}
	std::cout << "   [ Tree after inserting nodes 10, 20, 30 ] \n\n";
	AVLtree::print(root);

	for (int i = 1; i < 4; i++) {
		root = AVLtree::insert(root, -i * 10);
	}
	std::cout << "   [ Tree after inserting nodes -10, -20, -30 ] \n\n";
	AVLtree::print(root);
}

void main()
{
	test1();
	test2();
	std::getchar();
}
