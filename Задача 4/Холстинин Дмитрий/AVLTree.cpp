#include <algorithm>
#include <iostream>
#include <string>

template <class T>
class AVLTree
{
private:
	class Node
	{
	private:
		static unsigned char get_height(const Node *node)
		{
			return node ? node->height : 0;
		}

	public:
		T value;
		unsigned char height;
		Node *left, *right;

		Node(const T value) : value(value)
		{
			height = 1;
			left = right = 0;
		}

		int get_balance_factor()
		{
			return get_height(right) - get_height(left);
		}

		void restore_height()
		{
			height = std::max(get_height(left), get_height(right)) + 1;
		}
	};

	Node *root = 0;

	void dump(Node *node, std::string prefix = "", bool tail = true)
	{
		if (node)
		{
			if (node->right)
			{
				dump(node->right, prefix + (tail || node == root ? "    " : "|   "));
			}
			std::cout << prefix << "+-- " << node->value << std::endl;
			if (node->left)
			{
				dump(node->left, prefix + (!tail || node == root ? "    " : "|   "), false);
			}
		}
	}

	static Node* rotate_rigth(Node *p)
	{
		Node *q = p->left;
		p->left = q->right;
		q->right = p;
		p->restore_height();
		q->restore_height();
		return q;
	}

	static Node* rotate_left(Node *q)
	{
		Node *p = q->right;
		q->right = p->left;
		p->left = q;
		q->restore_height();
		p->restore_height();
		return p;
	}

	static Node* balance(Node *node)
	{
		node->restore_height();
		if (node->get_balance_factor() == 2)
		{
			if (node->right->get_balance_factor() < 0)
			{
				node->right = rotate_rigth(node->right);
			}
			return rotate_left(node);
		}
		if (node->get_balance_factor() == -2)
		{
			if (node->left->get_balance_factor() > 0)
			{
				node->left = rotate_left(node->left);
			}
			return rotate_rigth(node);
		}
		return node;
	}

	static Node* insert(Node *node, T value)
	{
		if (!node)
		{
			return new Node(value);
		}
		if (value < node->value)
		{
			node->left = insert(node->left, value);
		}
		else
		{
			node->right = insert(node->right, value);
		}
		return balance(node);
	}

	static Node* find_min(Node *node)
	{
		return node->left ? find_min(node->left) : node;
	}

	static Node* remove_min(Node *node)
	{
		if (!node->left)
		{
			return node->right;
		}
		node->left = remove_min(node->left);
		return balance(node);
	}

	static Node* remove(Node *node, T value)
	{
		if (!node)
		{
			return 0;
		}
		if (value < node->value)
		{
			node->left = remove(node->left, value);
		}
		else if (value > node->value)
		{
			node->right = remove(node->right, value);
		}
		else
		{
			Node *left = node->left;
			Node *right = node->right;
			delete node;
			if (!right)
			{
				return left;
			}
			Node *min = find_min(right);
			min->right = remove_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
	}

public:
	void insert(T value)
	{
		root = insert(root, value);
	}

	void remove(T value)
	{
		root = remove(root, value);
	}

	void balance()
	{
		root = balance(root);
	}

	void dump()
	{
		dump(root);
	}
};

int main()
{
	AVLTree<int> tree;
	const int length = 10 + 1;
	for (int i = 0; i < length; i++)
	{
		tree.insert(i);
		std::cout << "========== insert(" << i << ") ==========" << std::endl;
		tree.dump();
		std::cout << std::endl;
	}
	int value = std::rand() % length;
	for (int i = 0; i < length; i++)
	{
		tree.remove(value);
		std::cout << "========== remove(" << value << ") ==========" << std::endl;
		tree.dump();
		std::cout << std::endl;
		value = (value + 1) % length;
	}
	for (int i = 0; i < length; i++)
	{
		value = std::rand() % 10000;
		tree.insert(value);
		std::cout << "========== insert(" << value << ") ==========" << std::endl;
		tree.dump();
		std::cout << std::endl;
	}
}
