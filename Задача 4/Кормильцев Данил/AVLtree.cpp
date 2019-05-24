#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class node
{
public:
	int value;
	int height;
	node* left;
	node* right;

	node(int _value, int _height, node* _left, node* _right)
	{
		value = _value;
		height = _height;
		left = _left;
		right = _right;
	}

	node(int _value) : node(_value, 1, nullptr, nullptr)
	{

	}
};

class avl_tree
{
public:
	void print_tree()
	{
		print_from_node("", root, false);
		cout << endl;
	}

	void add(int number)
	{
		root = add(root, number);
	}

	void remove(int number)
	{
		remove(root, number);
	}

	void balance()
	{
		balance(root);
	}

private:

	node* root = nullptr;

	void print_from_node(const std::string& prefix, node* _node, bool isLeft)
	{
		if (_node != nullptr)
		{
			cout << prefix;
			std::cout << (isLeft ? "|--" : "|__");
			std::cout << _node->value << std::endl;
			print_from_node(prefix + (isLeft ? "|   " : "    "), _node->left, true);
			print_from_node(prefix + (isLeft ? "|   " : "    "), _node->right, false);
		}
	}

	void count_height(node* _node)
	{
		int left_height = get_height(_node->left);
		int right_height = get_height(_node->right);
		if(left_height > right_height)
		{
			_node->height = left_height + 1;
		}
		else
		{
			_node->height = right_height + 1;
		}
	}

	int get_difference(node* _node)
	{
		return get_height(_node->right) - get_height(_node->left);
	}

	int get_height(node* _node)
	{
		if(_node == nullptr)
		{
			return 0;
		}
		return _node->height;
	}

	node* add(node* _node, int value)
	{
		if (!_node)
			return new node(value);

		if (value < _node->value)
			_node->left = add(_node->left, value);
		else
			_node->right = add(_node->right, value);
		
		return balance(_node);
	}

	node* balance(node* _node)
	{
		count_height(_node);
		if (get_difference(_node) == 2)
		{
			if (get_difference(_node->right) < 0)
				_node->right = rotate_right(_node->right);
			return rotate_left(_node);
		}
		if (get_difference(_node) == -2)
		{
			if (get_difference(_node->left) > 0)
				_node->left = rotate_left(_node->left);
			return rotate_right(_node);
		}
		return _node;
	}

	node* rotate_right(node* _node)
	{
		node* q = _node->left;
		_node->left = q->right;
		q->right = _node;
		count_height(_node);
		count_height(q);
		return q;
	}

	node* rotate_left(node* _node)
	{
		node* p = _node->right;
		_node->right = p->left;
		p->left = _node;
		count_height(_node);
		count_height(p);
		return p;
	}

	node* remove(node* _node, int value)
	{
		if (!_node)
		{
			return nullptr;
		}
		if (value < _node->value)
		{
			_node->left = remove(_node->left, value);
		}
		else if (value > _node->value)
		{
			_node->right = remove(_node->right, value);
		}
		else
		{
			node* left = _node->left;
			node* right = _node->right;
			delete _node;
			if (!right) return left;
			node* min = find_min(right);
			min->right = remove_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(_node);
	}

	node* find_min(node* node)
	{
		if(node->left != nullptr)
		{
			return find_min(node->left);
		}
		return node;
	}

	node* remove_min(node* node)
	{
		if (node->left == nullptr)
			return node->right;
		node->left = remove_min(node->left);
		return balance(node);
	}
};

int main()
{
	auto tree = new avl_tree();
	tree->add(1);
	tree->add(2);
	tree->add(3);
	tree->print_tree();
	for(int i = 4; i < 15; i++)
	{
		tree->add(i);
	}
	tree->print_tree();
	tree->remove(12);
	tree->print_tree();
}

