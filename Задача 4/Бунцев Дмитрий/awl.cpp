#include "stdafx.h"
#include <iostream>

template <typename T>
class AwlTree
{
	T key;
	int height;
	AwlTree *left;
	AwlTree *right;

	static int getHeight(AwlTree *tree)
	{
		if (tree)
			return tree->height;
		return 0;
	}

	AwlTree* makeRotateRight(AwlTree *tree)
	{
		AwlTree *newTree = tree->left;
		tree->left = newTree->right;
		newTree->right = tree;
		tree->fixNodeHeight();
		newTree->fixNodeHeight();

		return newTree;
	}


	AwlTree* makeRotateLeft(AwlTree *tree)
	{

		AwlTree *newTree = tree->right;
		tree->right = newTree->left;
		newTree->left = tree;
		tree->fixNodeHeight();
		newTree->fixNodeHeight();

		return newTree;
	}

	int getBalanceFactor()
	{
		return getHeight(right) - getHeight(left);
	}

	void fixNodeHeight()
	{
		auto leftHeight = getHeight(left);
		auto rightHeight = getHeight(right);
		height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	AwlTree *equilibriumTree()
	{
		fixNodeHeight();
		if (getBalanceFactor() == 2) //big left rotate 
		{
			if (right->getBalanceFactor() < 0)
				right = makeRotateRight(right);
			return makeRotateLeft(this);
		}

		if (getBalanceFactor() == -2) // big right rotate
		{
			if (left->getBalanceFactor() > 0)
				left = makeRotateLeft(left);
			return makeRotateRight(this);
		}
		return this;
	}

	AwlTree *findMinimalKeyInSubtree()
	{
		return left ? left->findMinimalKeyInSubtree() : this;
	}

	AwlTree *removeMinimalSubtree()
	{
		if (!left)
			return right;
		left = left->removeMinimalSubtree();
		equilibriumTree();
	}

public:
	AwlTree(T key)
	{
		this->key = key;
		height = 1;
	}

	AwlTree *removeTree(T key)
	{
		if (key < this->key)
			left = left->removeTree(key);
		else if (this->key < key)
			right = right->removeTree(key);
		else
		{
			AwlTree *minInRightSubtree = right->findMinimalKeyInSubtree();
			minInRightSubtree->right = right->removeMinimalSubtree();
			minInRightSubtree->left = left;

			delete this;
			return minInRightSubtree->equilibriumTree();
		}
	}


	AwlTree* addTree(T key)
	{
		if (key >= this->key) 
		{
			if (!right)
				right = new AwlTree(key);
			else
				right->addTree(key);
		}
		else 
		{
			if (!left)
				left = new AwlTree(key);
			else
				left->addTree(key);
		}
		return this->equilibriumTree();
	}

	void traversal()
	{
		if (left)
			left->traversal();
		std::cout << key << std::endl;
		if (right)
			right->traversal();
	}
};

int main(int argc, char *argv[])
{
	AwlTree<double> *tree = new tree = tree->addTree(1);
	tree = tree->addTree(3);
	tree = tree->addTree(2);Tree<double>(2);
	tree = tree->addTree(1);
	tree = tree->addTree(3);
	tree = tree->addTree(2);
	tree = tree->addTree(13);
	tree = tree->addTree(28);
	tree = tree->addTree(228);
	tree = tree->addTree(1337);

	tree->traversal();
}