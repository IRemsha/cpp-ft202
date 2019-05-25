#pragma once
#include "node.h"
#include <string>
#include <iostream>

class avl_tree
{
	node* root_ = nullptr;

	static unsigned int height(node* n)
	{
		return n ? n->height : 0;
	}

	static int b_factor(node* n)
	{
		return height(n->right) - height(n->left);
	}

	static void fix_height(node* n)
	{
		auto hl = height(n->left);
		auto hr = height(n->right);
		n->height = (hl > hr ? hl : hr) + 1;
	}

	static node* rotate_right(node* n)
	{
		const auto q = n->left;
		n->left = q->right;
		q->right = n;
		fix_height(n);
		fix_height(q);
		return q;
	}

	static node* rotate_left(node* n)
	{
		const auto p = n->right;
		n->right = p->left;
		p->left = n;
		fix_height(n);
		fix_height(p);
		return p;
	}

	static node* balance(node* n)
	{
		fix_height(n);
		if (b_factor(n) == 2)
		{
			if (b_factor(n->right) < 0)
				n->right = rotate_right(n->right);
			return rotate_left(n);
		}
		if (b_factor(n) == -2)
		{
			if (b_factor(n->left) > 0)
				n->left = rotate_left(n->left);
			return rotate_right(n);
		}
		return n;
	}

	node* insert_node(node* n, const int key) const
	{
		if (!n) return new node(key);
		if (key < n->key)
			n->left = insert_node(n->left, key);
		else
			n->right = insert_node(n->right, key);
		return balance(n);
	}

	static node* find_min(node* n)
	{
		return n->left ? find_min(n->left) : n;
	}

	node* remove_min(node* n) const
	{
		if (n->left == nullptr)
			return n->right;
		n->left = remove_min(n->left);
		return balance(n);
	}

	node* remove_node(node* n, const int key) const
	{
		if (!n) return nullptr;
		if (key < n->key)
			n->left = remove_node(n->left, key);
		else if (key > n->key)
			n->right = remove_node(n->right, key);
		else
		{
			const auto q = n->left;
			const auto r = n->right;
			delete n;
			if (!r) return q;
			const auto min = find_min(r);
			min->right = remove_min(r);
			min->left = q;
			return balance(min);
		}
		return balance(n);
	}

	static void print_node(node* n, int tab_count, const bool is_left, const bool is_first)
	{
		if (!is_first)
		{
			for (auto i = 0; i < tab_count; i++)
				std::cout << "\t";
			std::cout << (is_left ? "left: " : "right: ");
			tab_count++;
		}

		std::cout << n->key << "\n";

		if (n->left)
			print_node(n->left, tab_count, true, false);
		if (n->right)
			print_node(n->right, tab_count, false, false);
	}

public:
	void insert(const int key)
	{
		root_ = insert_node(root_, key);
	}

	void remove(const int key)
	{
		root_ = remove_node(root_, key);
	}

	void balance()
	{
		if (root_)
			root_ = balance(root_);
	}

	void print() const
	{
		if (root_)
			print_node(root_, 0, false, true);
	}
};
