#include "pch.h"
#include <iostream>


class AVLTree {

	struct TreeNode {
		int element;
		TreeNode *left;
		TreeNode *right;
		int height;

		TreeNode(int el) {
			element = el;
			left = right = 0;
			height = 1;
		};
	};

	int GetHeight(TreeNode* p) {
		return p ? p->height : 0;
	}

	int GetHeightDiff(TreeNode* p) {
		return GetHeight(p->right) - GetHeight(p->left);
	}

	void UpdateHeight(TreeNode* p)	{
		auto left = GetHeight(p->left);
		auto right = GetHeight(p->right);
		p->height = (left > right ? left : right) + 1;
	}

	TreeNode* RotateRight(TreeNode* p) {
		auto q = p->left;
		p->left = q->right;
		q->right = p;
		UpdateHeight(p);
		UpdateHeight(q);
		return q;
	}

	TreeNode* RotateLeft(TreeNode* q) {
		auto p = q->right;
		q->right = p->left;
		p->left = q;
		UpdateHeight(q);
		UpdateHeight(p);
		return p;
	}

	TreeNode* ReqInsert(TreeNode* p, int el)
	{
		if (!p) {
			return new TreeNode(el);
		}
		if (el < p->element) {
			p->left = ReqInsert(p->left, el);
		}
		else {
			p->right = ReqInsert(p->right, el);
		}
		return BalanceFromNode(p);
	}

	TreeNode* BalanceFromNode(TreeNode* p) {
		UpdateHeight(p);
		if (GetHeightDiff(p) == 2) {
			if (GetHeightDiff(p->right) < 0) {
				p->right = RotateRight(p->right);
			}
			return RotateLeft(p);
		}
		if (GetHeightDiff(p) == -2) {
			if (GetHeightDiff(p->left) > 0) {
				p->left = RotateLeft(p->left);
			}
			return RotateRight(p);
		}
		return p;
	}

	TreeNode* FindMin(TreeNode* p) {
		return p->left ? FindMin(p->left) : p;
	}

	TreeNode* RemoveMin(TreeNode* p) {
		if (p->left == 0) {
			return p->right;
		}
		p->left = RemoveMin(p->left);
		return BalanceFromNode(p);
	}

	TreeNode* RemoveFromNode(TreeNode* p, int el) {
		if (!p) {
			return 0;
		}
		if (el < p->element) {
			p->left = RemoveFromNode(p->left, el);
		} else if (el > p->element) {
			p->right = RemoveFromNode(p->right, el);
		} else {
			auto q = p->left;
			auto r = p->right;
			delete p;
			if (!r) {
				return q;
			}
			auto min = FindMin(r);
			min->right = RemoveMin(r);
			min->left = q;
			return BalanceFromNode(min);
		}
		return BalanceFromNode(p);
	}

	void PrintFromNode(TreeNode *p, int n)  {
		if (p) {
			PrintFromNode(p->left, n + 5);
			for (auto i = 0; i < n; i++) {
				printf(" ");
			}
			printf("%d\n", p->element);
			PrintFromNode(p->right, n + 5);
		}
	}

public:
	TreeNode* root;
	AVLTree() {
		root = NULL;
	}

	AVLTree(int el) {
		root = &TreeNode(el);
	}

	void Insert(int el) {
		root = ReqInsert(root, el);
	}

	void Balance() {
		root = BalanceFromNode(root);
	}	

	void Remove(int el) {
		root = RemoveFromNode(root, el);
	}

	void Print() {
		PrintFromNode(root, 0);
	}
};


int main()
{
	auto tree = AVLTree();
	for (int i = 1; i < 11; i++) {
		tree.Insert(i);
	}
	printf("Tree from 1 to 10:\n");
	tree.Print();
	tree.Remove(6);
	printf("\nAfter removing 6:\n");
	tree.Print();
	tree.Remove(4);
	printf("\nAfter removing 4:\n");
	tree.Print();
	tree.Insert(5);
	printf("\nAfter inserting 5:\n");
	tree.Print();
	tree.Insert(15);
	printf("\nAfter inserting 15:\n");
	tree.Print();
	tree.Insert(25);
	printf("\nAfter inserting 25:\n");
	tree.Print();
}