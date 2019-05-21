// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#define NULL 0
using namespace std;


struct Node {
	int height;
	int value;
	Node *left;
	Node *right;
	Node(int value) {
		this->value = value;
		left = NULL;
		right = NULL;
		height = 1;
	}
	static int get_height(Node* node) {
		return node ? node->height : 0;
	}
	int diff() {
		return get_height(right) - get_height(left);
	}



};

class avl_tree {
public:
	avl_tree();
	~avl_tree();

	void insert(int key);
	Node *search(int key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	Node* get_max();
	Node* get_min();
	Node* remove(int key);

private:
	void destroy_tree(Node *leaf);
	Node* insert(Node *leaf, int key);
	Node *search(int key, Node *leaf);
	void inorder_print(Node *leaf);
	void postorder_print(Node *leaf);
	void preorder_print(Node *leaf);
	void adjuct_height(Node *node);
	Node* rotateLeft(Node *a);
	Node* rotateRight(Node *a);
	Node* remove_min(Node *node);
	Node* balance(Node *node);
	Node* get_max(Node* node);
	Node* get_min(Node* node);
	Node* remove(Node* tree, int key);

	Node *root;
};


avl_tree::avl_tree() {
	root = NULL;
}

avl_tree::~avl_tree() {
	destroy_tree();
}



void avl_tree::destroy_tree(Node *leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void avl_tree::adjuct_height(Node *node) {
	int left = Node::get_height(node->left);
	int right = Node::get_height(node->right);
	if (left > right)
		node->height = left + 1;
	else
		node->height = right + 1;
}

Node* avl_tree::rotateLeft(Node *node) {
	Node *b = node->right;
	node->right = b->left;
	b->left = node;
	adjuct_height(node);
	adjuct_height(b);
	return b;
}

Node* avl_tree::rotateRight(Node *node) {
	Node* b = node->left;
	node->left = b->right;
	b->right = node;
	adjuct_height(node);
	adjuct_height(b);
	return b;
}

Node* avl_tree::balance(Node *node) {
	adjuct_height(node);
	if (node->diff() == 2)
	{
		if (node->right->diff() < 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	if (node->diff() == -2)
	{
		if (node->left->diff() > 0)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node;
}


Node* avl_tree::insert(Node* node, int key) {

	if (node == NULL) return new Node(key);
	if (key < node->value)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);
	return balance(node);
}
void avl_tree::insert(int key) {
	if (root != NULL) {
		root = insert(root, key);
	}
	else {
		root = new Node(key);
	}
}

Node *avl_tree::search(int key, Node *leaf) {
	if (leaf != NULL) {
		if (key == leaf->value) {
			return leaf;
		}
		if (key < leaf->value) {
			return search(key, leaf->left);
		}
		else {
			return search(key, leaf->right);
		}
	}
	else {
		return NULL;
	}
}

Node *avl_tree::search(int key) {
	return search(key, root);
}

void avl_tree::destroy_tree() {
	destroy_tree(root);
}

void avl_tree::inorder_print() {
	inorder_print(root);
	cout << "\n";
}

void avl_tree::inorder_print(Node *leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void avl_tree::postorder_print() {
	postorder_print(root);
	cout << "\n";
}

void avl_tree::postorder_print(Node *leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}

void avl_tree::preorder_print() {
	preorder_print(root);
	cout << "\n";
}

void avl_tree::preorder_print(Node *leaf) {
	if (leaf != NULL) {
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}

Node* avl_tree::get_min(Node* node)
{
	return node->left ? get_min(node->left) : node;
}

Node* avl_tree::get_min() {
	return root ? get_min(root) : NULL;
}
Node* avl_tree::get_max(Node* node)
{
	return node->right ? get_min(node->right) : node;
}


Node* avl_tree::get_max() {
	return root ? get_max(root) : NULL;
}

Node* avl_tree::remove(Node* tree, int key) {
	if (!tree)
		return NULL;
	if (key < tree->value)
		tree->left = remove(tree->left, key);
	else if (key > tree->value)
		tree->right = remove(tree->left, key);
	else
	{
		Node* left = tree->left;
		Node* right = tree->right;
		delete tree;
		if (!right) return left;
		Node* min = get_min(right);
		min->right = remove_min(right);
		min->left = left;
		return balance(min);
	}
	return balance(tree);
}

Node* avl_tree::remove(int key) {
	return root ? remove(root,key) : NULL;

}
Node* avl_tree::remove_min(Node* node) {
	if (node->left == NULL)
		return node->right;
	node->left = remove_min(node->left);
	return balance(node);
}

int main() {

	avl_tree *tree = new avl_tree();

	tree->insert(5);
	tree->insert(8);
	tree->insert(24);
	tree->insert(6);
	tree->insert(10);

	tree->postorder_print();
	tree->preorder_print();
	tree->inorder_print();

	tree->remove(5);
	tree->postorder_print();
	printf("\ninserting 7:\n");
	tree->insert(7);
	tree->postorder_print();
	printf("\nremoving 6:\n");
	tree->remove(6);
	tree->postorder_print();


	delete tree;

}