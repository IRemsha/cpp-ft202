
#include<iostream>
#include<string>

using namespace std;

struct Node
{
	int value;
	unsigned char height;
	Node* left;
	Node* right;

	Node(int n) {
		value = n;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

class AVLTree
{
private:
	Node * root = NULL;

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
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if (!right)
				return left;
			Node* min = find_min(right);
			min->right = remove_min_node(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
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

	Node* balance(Node* node)
	{
		recount_height(node);
		if (get_balance_factor(node) == 2)
		{
			if (get_balance_factor(node->right) < 0)
				node->right = rotate_right(node->right);
			return rotate_left(node);
		}
		if (get_balance_factor(node) == -2)
		{
			if (get_balance_factor(node->left) > 0)
				node->left = rotate_left(node->left);
			return rotate_right(node);
		}
		return node;
	}

	Node* find_min(Node* node)
	{
		return node->left ? find_min(node->left) : node;
	}

	Node* remove_min_node(Node* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = remove_min_node(node->left);
		return balance(node);
	}

	Node* rotate_right(Node* node)
	{
		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		recount_height(node);
		recount_height(left);
		return left;
	}

	Node* rotate_left(Node* node)
	{
		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		recount_height(node);
		recount_height(right);
		return right;
	}
	
	void recount_height(Node* node)
	{
		unsigned char left_h = height(node->left);
		unsigned char right_h = height(node->right);
		node->height = (left_h > right_h ? left_h : right_h) + 1;
	}
	
	unsigned char height(Node* node)
	{
		return node ? node->height : 0;
	}

	int get_balance_factor(Node* node)
	{
		return height(node->right) - height(node->left);
	}

	void print(Node* node, int indent = 0) {
		if (node) {
			for (int i = 0; i < indent; i++)
				cout << " ";
			cout << node->value << "\n ";
			if (node->left)
				print(node->left, indent + 4);
			if (node->right)
				print(node->right, indent + 4);

		}
	}

public:
	void insert(int key) {
		root = insert(root, key);
	}

	void balance() {
		root = balance(root);
	}

	void remove(int key) {
		root = remove(root, key);
	}

	void print() {
		print(root);
	}
};

int main() {
	auto tree = new AVLTree();
	cout << endl << "Add six elements" << endl;
	for (int i = 0; i < 6; i++)
		tree->insert(i);
	tree->print();
	cout << endl << "Remove element not exist" << endl;
	tree->remove(15);
	tree->print();
	cout << endl << "Insert element" << endl;
	tree->insert(9);
	tree->print();
	cout << endl << "Remove root" << endl;
	tree->remove(3);
	tree->print();
	
	cout << endl << "Remove leaf" << endl;
	tree->remove(9);
	tree->print();
}
