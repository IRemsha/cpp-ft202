#pragma once
#include "node.h"
#include <string>
#include <iostream>

class avl_tree
{
	node* root_ = nullptr;

	unsigned int height(node* p)
	{
		return p ? p->height : 0;
	}

	int bfactor(node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fix_height(node* p)
	{
		auto hl = height(p->left);
		auto hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node* rotate_right(node* p) // правый поворот вокруг p
	{
		const auto q = p->left;
		p->left = q->right;
		q->right = p;
		fix_height(p);
		fix_height(q);
		return q;
	}

	node* rotate_left(node* q) // левый поворот вокруг q
	{
		const auto p = q->right;
		q->right = p->left;
		p->left = q;
		fix_height(q);
		fix_height(p);
		return p;
	}

	node* balance(node* p) // балансировка узла p
	{
		fix_height(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotate_right(p->right);
			return rotate_left(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotate_left(p->left);
			return rotate_right(p);
		}
		return p; // балансировка не нужна
	}

	node* insert_node(node* p, const int k) // вставка ключа k в дерево с корнем p
	{
		if (!p) return new node(k);
		if (k < p->key)
			p->left = insert_node(p->left, k);
		else
			p->right = insert_node(p->right, k);
		return balance(p);
	}

	node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	node* remove_min(node* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == nullptr)
			return p->right;
		p->left = remove_min(p->left);
		return balance(p);
	}

	node* remove_node(node* p, const int k) // удаление ключа k из дерева p
	{
		if (!p) return nullptr;
		if (k < p->key)
			p->left = remove_node(p->left, k);
		else if (k > p->key)
			p->right = remove_node(p->right, k);
		else //  k == p->key 
		{
			const auto q = p->left;
			const auto r = p->right;
			delete p;
			if (!r) return q;
			const auto min = findmin(r);
			min->right = remove_min(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	static void print_node(node* n, const std::string& prefix, const bool is_left, const bool is_first)
	{
		auto new_prefix = prefix;
		if (!is_first)
		{
			std::cout << prefix << "|\n";
			std::cout << prefix << (is_left ? "|--(L)--> " : "+--(R)--> ");

			if (is_left)
				new_prefix += "|";
			else
				new_prefix += " ";
			new_prefix += "         ";
		}

		std::cout << n->key << "\n";

		if (n->left)
			print_node(n->left, new_prefix, true, false);
		if (n->right)
			print_node(n->right, new_prefix, false, false);
	}

public:
	//avl_tree() = default;

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
		if(root_)
			root_ = balance(root_);
	}

	void print() const
	{
		if (root_)
			print_node(root_, "", false, true);
	}
};
