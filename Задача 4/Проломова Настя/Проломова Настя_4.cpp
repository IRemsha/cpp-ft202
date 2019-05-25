#include<iostream>
#include<string>

using namespace std;

struct Node
{
	int key;
	unsigned char height;
	Node* left;
	Node* right;

	Node(int n) {
		key = n;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

class AVLTree
{
private:
	Node* root = NULL;

	Node* insert_key(Node* node, int key)
	{
		if (!node) return new Node(key);
		if (key < node->key)
			node->left = insert_key(node->left, key);
		else
			node->right = insert_key(node->right, key);
		return balance_tree(node);
	}

	Node* remove_key(Node* node, int key)
	{
		if (!node)
			return 0;
		if (key < node->key)
			node->left = remove_key(node->left, key);
		else if (key > node->key)
			node->right = remove_key(node->right, key);
		else //  k == p->key 
		{
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if (!right)
				return left;
			Node* min = find_min_key(right);
			min->right = remove_min_key_node(right);
			min->left = left;
			return balance_tree(min);
		}
		return balance_tree(node);
	}

	Node* find_min_key(Node* node)
	{
		return node->left ? find_min_key(node->left) : node;
	}

	Node* remove_min_key_node(Node* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = remove_min_key_node(node->left);
		return balance_tree(node);
	}

	Node* balance_tree(Node* node)
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

	unsigned char height(Node* node)
	{
		return node ? node->height : 0;
	}

	int get_balance_factor(Node* node)
	{
		return height(node->right) - height(node->left);
	}

	void recount_height(Node* node)
	{
		unsigned char left_h = height(node->left);
		unsigned char right_h = height(node->right);
		node->height = (left_h > right_h ? left_h : right_h) + 1;
	}

	void print_node(Node* node, int indent = 0) {
		if (node) {
			for (int i = 0; i < indent; i++)
				cout << " ";
			cout << node->key << "\n ";
			if (node->left)
				print_node(node->left, indent + 4);
			if (node->right)
				print_node(node->right, indent + 4);

		}
	}

public:
	void insert(int key) {
		root = insert_key(root, key);
	}

	void balance() {
		root = balance_tree(root);
	}

	void remove(int key) {
		root = remove_key(root, key);
	}

	void print() {
		print_node(root);
	}
};

int main() {
	auto tree = new AVLTree();
	cout << endl << "_____Add_5_elements_____" << endl;
	for (int i = 0; i < 5; i++) 
		tree->insert(i);		
	tree->print();
	cout << endl << "_____Insert_element_____" << endl;
	tree->insert(8);
	tree->print();
	cout << endl << "_____Remove_root_____" << endl;
	tree->remove(3);
	tree->print();
	cout << endl << "_____Remove_nonexistent_element_____" << endl;
	tree->remove(10);
	tree->print();
	cout << endl << "_____Remove_leaf_____" << endl;
	tree->remove(8);
	tree->print();
}