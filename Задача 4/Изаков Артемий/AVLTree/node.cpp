#include "node.h"
#include <stdexcept>
#include <iostream>

using namespace std;

node::node(const int value)
{
	this->value = value;
	left = right = nullptr;
	height = 1;
}

int node::get_balance_factor() const
{
	const auto left_height = left ? left->height : 0;
	const auto right_height = right ? right->height : 0;
	return right_height - left_height;
}

void node::update_height()
{
	const auto left_height = left ? left->height : 0;
	const auto right_height = right ? right->height : 0;
	height = left_height > right_height ? left_height : right_height;
	height++;
}

node* node::rotate_left()
{
	auto current = right;
	right = current->left;
	current->left = this;

	update_height();
	current->update_height();

	return current;
}

node* node::rotate_right()
{
	auto current = left;
	left = current->right;
	current->right = this;

	update_height();
	current->update_height();

	return current;
}

node* node::balance()
{
	update_height();
	const auto balance_factor = get_balance_factor();

	if (balance_factor == 2)
	{
		if (right->get_balance_factor() < 0)
			right = right->rotate_right();
		return rotate_left();
	}

	if (balance_factor == -2)
	{
		if (left->get_balance_factor() > 0)
			left = left->rotate_left();
		return rotate_left();
	}

	return this;
}

node* node::insert(const int new_value)
{
	if (new_value < value)
		left = left ? left->insert(new_value) : new node(new_value);
	else
		right = right ? right->insert(new_value) : new node(new_value);
	return balance();
}

node* node::get_min()
{
	return left ? left->get_min() : this;
}

node* node::remove_min()
{
	if (!left)
		return right;
	left = left->remove_min();
	return balance();
}

node* node::remove(const int value_to_remove)
{
	if (value_to_remove < value)
	{
		if (!left)
			throw out_of_range("no such item to remove");
		left = left->remove(value_to_remove);
	}
	else if (value_to_remove > value)
	{
		{
			if (!right)
				throw out_of_range("no such item to remove");
			right = right->remove(value_to_remove);
		}
	}
	else
	{
		const auto left_root = left;
		const auto right_root = right;
		delete this;
		if (!right_root)
			return left_root;
		auto min = right_root->get_min();
		min->right = right_root->remove_min();
		min->left = left_root;
		return min->balance();
	}

	return balance();
}

void node::print(const string& prefix, const bool is_left, const bool is_first) const
{
	auto new_prefix = prefix;
	if (!is_first)
	{
		cout << prefix << "|\n";
		cout << prefix << (is_left ? "|--(L)--> " : "+--(R)--> ");

		if (is_left)
			new_prefix += "|";
		else
			new_prefix += " ";
		new_prefix += "         ";
	}

	cout << value << endl;

	if (left)
		left->print(new_prefix, true);
	if (right)
		right->print(new_prefix, false);
}
