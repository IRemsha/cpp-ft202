#include "AvlTree.h"

AvlTree::~AvlTree()
{
    delete root;
}

void AvlTree::Insert(int key)
{
    root = Insert(root, key);
}

void AvlTree::Remove(int key)
{
    root = RemoveKey(root, key);
}

std::vector<int> AvlTree::GetKeys()
{
    std::vector<int> sortedKeys;
    TraverseTree(root, sortedKeys);

    return sortedKeys;
}

void AvlTree::TraverseTree(Node* treeRoot, std::vector<int>& vector)
{
    while (true)
    {
        if (treeRoot == nullptr) return;

        TraverseTree(treeRoot->leftSubtree, vector);

        vector.push_back(treeRoot->key);

        treeRoot = treeRoot->rightSubtree;
    }
}

void AvlTree::PrintTree()
{
    if (root == nullptr)
        std::cout << "Tree is empty." << std::endl;
    else
        PrintTree("", root, false);
}

void AvlTree::PrintTree(const std::string& prefix, const Node* node, bool isLeft)
{
    if (node == nullptr) return;

    std::cout << prefix << (isLeft ? "├──" : "└──" ) << node->key << std::endl;

    PrintTree(prefix + (isLeft ? "│   " : "    "), node->leftSubtree, true);
    PrintTree(prefix + (isLeft ? "│   " : "    "), node->rightSubtree, false);
}

char AvlTree::CalculateBalanceFactor(Node* treeRoot)
{
    return Node::GetTreeHeight(treeRoot->rightSubtree) - Node::GetTreeHeight(treeRoot->leftSubtree);
}

Node* AvlTree::Balance(Node* treeRoot)
{
    treeRoot->RecalculateTreeHeight();

    if (CalculateBalanceFactor(treeRoot) == 2)
    {
        if (CalculateBalanceFactor(treeRoot->rightSubtree) < 0)
            treeRoot->rightSubtree = treeRoot->rightSubtree->RotateToRight();
        return treeRoot->RotateToLeft();
    }

    if (CalculateBalanceFactor(treeRoot) == -2)
    {
        if (CalculateBalanceFactor(treeRoot->leftSubtree) > 0)
            treeRoot->leftSubtree = treeRoot->leftSubtree->RotateToLeft();
        return treeRoot->RotateToRight();
    }

    return treeRoot;
}

Node* AvlTree::Insert(Node* treeRoot, int key)
{
    if (!treeRoot) return new Node(key);

    if (key < treeRoot->key)
        treeRoot->leftSubtree = Insert(treeRoot->leftSubtree, key);
    else
        treeRoot->rightSubtree = Insert(treeRoot->rightSubtree, key);

    return Balance(treeRoot);
}

Node* AvlTree::FindMinNode(Node* treeRoot)
{
    return treeRoot->leftSubtree ? FindMinNode(treeRoot->leftSubtree) : treeRoot;
}

Node* AvlTree::RemoveMinKey(Node* treeRoot)
{
    if (treeRoot->leftSubtree == nullptr)
        return treeRoot->rightSubtree;
    treeRoot->leftSubtree = RemoveMinKey(treeRoot->leftSubtree);

    return Balance(treeRoot);
}

Node* AvlTree::RemoveKey(Node* treeRoot, int removedKey)
{
    if (!treeRoot) throw std::out_of_range("Not found specified key.");

    if (removedKey < treeRoot->key)
        treeRoot->leftSubtree = RemoveKey(treeRoot->leftSubtree, removedKey);
    else if (removedKey > treeRoot->key)
        treeRoot->rightSubtree = RemoveKey(treeRoot->rightSubtree, removedKey);
    else
    {
        Node* leftSubtree = treeRoot->leftSubtree;
        Node* rightSubtree = treeRoot->rightSubtree;
        delete treeRoot;

        if (!rightSubtree) return leftSubtree;

        Node* minNode = FindMinNode(rightSubtree);
        minNode->rightSubtree = RemoveMinKey(rightSubtree);
        minNode->leftSubtree = leftSubtree;

        return Balance(minNode);
    }

    return Balance(treeRoot);
}
