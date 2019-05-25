#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>

class AVLTree
{
	struct node
	{
		int key;
		unsigned char height = 1;
		node* left = nullptr;
		node* right = nullptr;
		node(int key) : key(key) {}

		void update_height()
		{
			
			height = std::max(left != nullptr ? left->height : 0,
				right != nullptr ? right->height : 0) + 1;
		}

	};

	node* root = nullptr;

	node* insert(node* parent, int value)
	{
		if (parent == nullptr)
			return new node(value);
		if (value < parent->key)
			parent->left = insert(parent->left, value);
		else
			parent->right = insert(parent->right, value);
		return balance(parent);
	}

	node* remove(node* cur_node, int value)
	{
		if (cur_node == nullptr)
			return cur_node;
		if (value < cur_node->key)
			cur_node->left = remove(cur_node->left, value);
		else if (value > cur_node->key)
			cur_node->right = remove(cur_node->right, value);
		else
		{
			auto left_child = cur_node->left;
			auto right_child = cur_node->right;
			if (!right_child)
				return left_child;
			auto min_node = get_min_node(right_child);
			min_node->right = remove_min(right_child);
			min_node->left = left_child;
			return balance(min_node);
		}
		return balance(cur_node);
	}


	node* remove_min(node* cur_node)
	{
		if (cur_node->left == nullptr)
			return cur_node->right;
		cur_node->left = remove_min(cur_node->left);
		return balance(cur_node);
	}

	node* balance(node* parent)
	{
		parent->update_height();
		auto factor = bfactor(parent);
		if (factor == 2)
		{
			auto right_factor = bfactor(parent->right);
			if (right_factor < 0)
				parent->right = rotate_right(parent->right);
			return rotate_left(parent);
		}
		if (factor != -2)
			return parent;
		auto left_factor = bfactor(parent->left);
		if (left_factor > 0)
			parent->left = rotate_left(parent->left);
		return rotate_right(parent);
	}

	node* rotate_right(node* parent)
	{
		auto left_child = parent->left;
		parent->left = left_child->right;
		left_child->right = parent;
		parent->update_height();
		left_child->update_height();
		return left_child;
	}

	node* rotate_left(node* parent)
	{
		auto right_child = parent->right;
		parent->right = right_child->left;
		right_child->left = parent;
		parent->update_height();
		right_child->update_height();
		return right_child;
	}

	int bfactor(node* cur_node)
	{
		return get_height(cur_node->right) - get_height(cur_node->left);
	}

	int get_height(node* cur_node)
	{
		return cur_node != nullptr ? cur_node->height : 0;
	}

	node* get_min_node(node* cur_node)
	{
		return cur_node->left == nullptr ? cur_node : cur_node->left;
	}

	std::vector<int>* get_sorted_items()
	{
		std::vector<int>* values = new std::vector<int>();
		std::stack<node*> right_items;
		auto cur_node = root;
		while (cur_node != nullptr)
		{
			while (cur_node != nullptr)
			{
				right_items.push(cur_node);
				cur_node = cur_node->left;
			}
			while (cur_node == nullptr && !right_items.empty())
			{
				cur_node = right_items.top();
				right_items.pop();
				values->push_back(cur_node->key);
				cur_node = cur_node->right;
			}
		}
		return values;
	}

public:

	void add(int value)
	{
		root = insert(root, value);
	}

	void remove(int value)
	{
		root = remove(root, value);
	}

	void print_items()
	{
		std::vector<int> items = *get_sorted_items();
		printf_s("******************************\n");
		printf_s("Height of tree equals to %d\n", get_height(root));
		printf_s("Total items count equals to %d\n", items.size());
		for (auto u : items)
			printf_s("%d\n", u);
		printf_s("******************************\n");

	}

	void clear()
	{
		root = nullptr;
	}

	int height()
	{
		return get_height(root);
	}
};

int main()
{
	AVLTree tree;

	printf_s("Tree get many operations\n");
	printf_s("To tree was added [1,3,5]\n");
	tree.add(5);
	tree.add(1);
	tree.add(3);
	tree.print_items();
	tree.remove(3);
	tree.add(11);
	tree.add(-11);
	printf_s("To tree were added [11, -11] and was removed [3]\n");
	tree.print_items();
	tree.remove(-11);
	tree.add(20);
	tree.remove(1);
	tree.add(31);
	printf_s("To tree were added [20, 31] and were removed [1, -11]\n");
	tree.print_items();
	tree.clear();


	printf_s("Tree gets consecutive numbers\n");
	for (int i = 0; i < 10; i++)
	{
		tree.add(i);
	}
	tree.remove(5);
	tree.print_items();
	tree.clear();

	printf_s("Tree gets random numbers\n");
	for (int i = 0; i < 20; i++)
		tree.add((i * i) % 13);
	tree.print_items();
	tree.clear();

	printf_s("Tree gets repetitive elements and remove one of them\n");
	printf_s("[3, 10, 2, 3, 3] were given to tree and 3 was removed\n");
	tree.add(3);
	tree.add(10);
	tree.add(2);
	tree.add(3);
	tree.add(3);
	tree.remove(3);
	tree.print_items();
	tree.clear();

	printf_s("Test of work with many items\n");
	printf_s("Added 10000 elements\n");
	auto start_time = std::chrono::system_clock::now();
	for (int i = 0; i < 10000; i++)
		tree.add(rand());
	auto end_time = std::chrono::system_clock::now();
	auto difference = end_time - start_time;
	tree.clear();

	printf_s("Total time of work %lld ticks\n\n", difference.count());
	printf_s("Test height of tree with big consequence of numbers: 100000 numbers\n");
	for (int i = 0; i < 100000; i++)
		tree.add(i);
	printf_s("Height of tree is %d\n", tree.height());
	


	return 0;

}