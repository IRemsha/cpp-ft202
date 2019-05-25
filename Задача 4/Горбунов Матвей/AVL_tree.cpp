#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
	int value;
	unsigned char height;
	Node* left;
	Node* right;
	Node(int v)
	{
		value = v;
		left = 0;
		right = 0;
		height = 1;
	}
};

class AVL_tree
{
private:
	unsigned char get_height(Node* node)
	{
		return node ? node->height : 0;
	}

	int get_balance_factor(Node* node)
	{
		return get_height(node->right) - get_height(node->left);
	}

	void fix_height(Node* node)
	{
		unsigned char hl = get_height(node->left);
		unsigned char hr = get_height(node->right);
		node->height = (hl > hr ? hl : hr) + 1;
	}

	Node* rotate_right(Node* node) 
	{
		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		fix_height(node);
		fix_height(left);
		return left;
	}

	Node* rotate_left(Node* node) 
	{
		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		fix_height(node);
		fix_height(right);
		return right;
	}

	Node* balance(Node* to_balance) 
	{
		fix_height(to_balance);
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

	Node* insert(Node* node, int val) 
	{
		if (!node) return new Node(val);
		if (val < node->value)
			node->left = insert(node->left, val);
		else
			node->right = insert(node->right, val);
		return balance(node);
	}

	Node* find_min(Node* node)
	{
		return node->left ? find_min(node->left) : node;
	}

	Node* remove_min(Node* node)
	{
		if (node->left == 0)
			return node->right;
		node->left = remove_min(node->left);
		return balance(node);
	}

	void postorder(Node* p, int indent = 0)
	{
		if (p != 0) {
			if (p->right) {
				postorder(p->right, indent + 4);
			}
			if (indent) {
				std::cout << std::setw(indent) << ' ';
			}
			if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
			std::cout << p->value << "\n ";
			if (p->left) {
				std::cout << std::setw(indent) << ' ' << " \\\n";
				postorder(p->left, indent + 4);
			}
		}
	}

	Node* remove(Node* node, int val) 
	{
		if (!node) return 0;
		if (val < node->value)
			node->left = remove(node->left, val);
		else if (val > node->value)
			node->right = remove(node->right, val);
		else 
		{
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if (!right)
				return left;
			Node* min = find_min(right);
			min->right = remove_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
	}
public:
	Node* root;

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
		postorder(root);
	}
};

int main() {
	auto tree = new AVL_tree();
	cout << "Create Tree" << endl;
	for (int i = 0; i <10; i++)
		tree->insert(i);
	tree->print();

	cout << "Remove 5" << endl;
	tree->remove(5);
	tree->print();

	cout << "Add 5" << endl;
	tree->insert(5);
	tree->print();

	cout << "Add 10" << endl;
	tree->insert(10);
	tree->print();

	cout << "Remove 7" << endl;
	tree->remove(7);
	tree->print();
}