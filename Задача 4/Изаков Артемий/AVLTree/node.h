#pragma once
#include <string>

using namespace std;

struct node
{
	int value;
	int height;
	node* left;
	node* right;

	node(int value);

	int get_balance_factor() const;

	void update_height();

	node* rotate_left();

	node* rotate_right();

	node* balance();

	node* insert(int new_value);

	node* get_min();

	node* remove_min();

	node* remove(int value_to_remove);

	void print(const string& prefix, bool is_left, bool is_first = false) const;
};
