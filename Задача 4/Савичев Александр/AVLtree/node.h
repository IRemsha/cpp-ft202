#pragma once

struct node
{
	int key;
	unsigned int height;
	node* left;
	node* right;
	explicit node(const int k) { key = k; left = right = nullptr; height = 1; }
};