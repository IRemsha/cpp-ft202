#include<iostream>
#include<string>

using namespace std;

struct NodeTree
{
	int key;
	unsigned char height;
	NodeTree* left;
	NodeTree* right;

	NodeTree(int n) {
		key = n;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

class AVL
{
	NodeTree* root = NULL;

	NodeTree* insert(NodeTree* node, int key)
	{
		if (!node) return new NodeTree(key);
		if (key < node->key)
			node->left = insert(node->left, key);
		else
			node->right = insert(node->right, key);
		return balance(node);
	}

	unsigned char height(NodeTree* node)
	{
		return node ? node->height : 0;
	}

	int getBalance(NodeTree* node)
	{
		return height(node->right) - height(node->left);
	}

	NodeTree* findMin(NodeTree* node)
	{
		return node->left ? findMin(node->left) : node;
	}

	NodeTree* removeMin(NodeTree* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = removeMin(node->left);
		return balance(node);
	}

	NodeTree* remove(NodeTree* node, int key)
	{
		if (!node)
			return 0;
		if (key < node->key)
			node->left = remove(node->left, key);
		else if (key > node->key)
			node->right = remove(node->right, key);
		else //  k == p->key 
		{
			NodeTree* left = node->left;
			NodeTree* right = node->right;
			delete node;
			if (!right)
				return left;
			NodeTree* min = findMin(right);
			min->right = removeMin(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
	}

	NodeTree* rotateRight(NodeTree* node)
	{
		NodeTree* left = node->left;
		node->left = left->right;
		left->right = node;
		getHeight(node);
		getHeight(left);
		return left;
	}

	NodeTree* rotateLeft(NodeTree* node)
	{
		NodeTree* right = node->right;
		node->right = right->left;
		right->left = node;
		getHeight(node);
		getHeight(right);
		return right;
	}

	NodeTree* balance(NodeTree* node)
	{
		getHeight(node);
		if (getBalance(node) == 2)
		{
			if (getBalance(node->right) < 0)
				node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
		if (getBalance(node) == -2)
		{
			if (getBalance(node->left) > 0)
				node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		return node;
	}

	void getHeight(NodeTree* node)
	{
		unsigned char left_height = height(node->left);
		unsigned char right_height = height(node->right);
		if (left_height > right_height) 
			node->height = left_height + 1;
		else
			node->height = right_height + 1;
	}

public:
	void balance() {
		root = balance(root);
	}

	void remove(int key) {
		root = remove(root, key);
	}

	void insert(int key) {
		root = insert(root, key);
	}

	void printNode(NodeTree* node, int level, string site) {

		NodeTree* left = node->left;
		NodeTree* right = node->right;
		int keyLeft = left ? left->key : -1;
		int keyRight = right ? right->key : -1;
		if (node) {
			if (level == 0)
				cout<< "level " << level << " root " << "key " << node->key <<'\n';
			cout <<"site "<< site << " level " << level << " left " << keyLeft << " right " << keyRight << '\n';
			if (left)
				printNode(left, level + 1, "left ");
			if (right)
				printNode(right, level + 1, "right ");
		}
	}

	void print() {
		printNode(root, 0, "root");
	}
};

int main() {
	AVL* tree = new AVL();
	for (int i = 0; i < 10; i++)
		tree->insert(i);
	tree->print();
	tree->insert(13);
	tree->print();
	tree->remove(5);
	tree->print();
	tree->remove(10);
	tree->print();
}