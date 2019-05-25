#include <algorithm>
using namespace std;

struct node
{
	int key;
	int height;
	struct node *left;
	struct node *right;
	bool deleted;
};

 node *createNode(int nodeKey)
{
	node*newNode;
	newNode = new node;
	if (newNode != nullptr) {
		newNode->key = nodeKey;
		newNode->height = 0;
		newNode->left = newNode->right = nullptr;
		newNode->deleted = false;
	}
	return newNode;
}

int subTreeHeight(node *root)
{
	return(root != nullptr) ? root->height : -1;
}

bool treeBalance(node *root)
{
	return (subTreeHeight(root->left) - subTreeHeight(root->right) > 1) ? false : true; 
}


 node *rightRotate( node *root)
{
	node *left;
	left = root->left;
	root->left = left->right;
	left->right = root;
	root->height = max(subTreeHeight(root->left), subTreeHeight(root->right)) + 1;
	left->height = max(subTreeHeight(left->left), root->height) + 1;
	return left;
}

node *leftRotate(node *root)
{
	node *right;
	right = root->right;
	root->right = right->left;
	right->left = root;
	root->height = max(subTreeHeight(root->left), subTreeHeight(root->right)) + 1;
	right->height = max(subTreeHeight(right->right), root->height) + 1;
	return right;
}

node *leftRightRotate(node *root)
{
	root->left = leftRotate(root->left);
	return rightRotate(root);
}

node *rightLeftRotate(node *root)
{
	root->right = rightRotate(root->right);
	return leftRotate(root);
}

int getNodeBalance(node* v)
{
	return (v->left != nullptr) ? v->left->height : 0 - (v->right != nullptr) ? v->right->height : 0;
}

node *balancedTree(node* root)
{
	root->height = max(subTreeHeight(root->left), subTreeHeight(root->right)) + 1;
	int balance = subTreeHeight(root->left) - subTreeHeight(root->right);
	if (balance == -2) {
		if (getNodeBalance(root->right) > 0) {
			//левый-правый поворот
			root = rightLeftRotate(root);
		}
		else {
			//левый поворот
			root = leftRotate(root);
		}
	}
	else if (balance == 2) {
		if (getNodeBalance(root->left) > 0) {
			root = leftRightRotate(root);
		}
		else {
			root = rightRotate(root);
		}
	}
	return root;
}

node *addNode(node *root, int key)
{
	if (root == nullptr) {
		return createNode(key);
	}

	if (key < root->key) {
		root->left = addNode(root->left, key);
	}
	else if (key > root->key) {
		root->right = addNode(root->right, key);
	}
	return balancedTree(root);
}


node *findMinNode(node *root)
{
	if(root->left == nullptr) return root;
	return findMinNode(root->left);
}

node *removeMin(node *root)
{
	if (root->left == nullptr)
		return root->right;
	root->left = removeMin(root->left);
	return balancedTree(root);
}

node *avlTreeDel(node *root, int keyToDel)
{
	if (root == nullptr) {
		return 0;
	}
	int currentValue = root->key;
	if (keyToDel > currentValue)
	{
		root->right = avlTreeDel(root->right, keyToDel);
	}
	else if (keyToDel < currentValue)
	{
		root->left = avlTreeDel(root->left, keyToDel);
	}
	else
	{
		node* leftNode = root->left;
		node* rightNode = root->right;
		delete root;
		if (!rightNode)
			return leftNode;
		node * minNode = findMinNode(rightNode);
		minNode->right = removeMin(rightNode);
		minNode->left = leftNode;
		return balancedTree(minNode);
	}
	return balancedTree(root);
}

void printAvlTree(node *root, int level)
{
	node *tmpRoot = root;
	if (tmpRoot == nullptr) return;
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%d\n", tmpRoot->key);
	printAvlTree(tmpRoot->left, level + 1);
	printAvlTree(tmpRoot->right, level + 1);
}

 int main()
{
	node *root = nullptr;
	root = addNode(root, 10);
	root = addNode(root, 5);
	root = addNode(root, 3);
	root = addNode(root, 11);
	root = addNode(root, 12);
	printAvlTree(root, 0);
	root = avlTreeDel(root, 5);
	printAvlTree(root, 0);
	return 0;
}