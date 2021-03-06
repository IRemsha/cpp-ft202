﻿#pragma once
#include "node.h"

class avl_tree
{
	node* root = nullptr;

public:
	void insert(int value);

	void remove(int value);

	void print() const;

	void balance();
};
