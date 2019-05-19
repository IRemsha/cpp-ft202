#include "Node.h"

Node::Node(int key) : key(key), leftSubtree(nullptr), rightSubtree(nullptr), treeHeight(1) { }

unsigned char Node::GetTreeHeight(Node* treeRoot)
{
    return treeRoot == nullptr ? 0 : treeRoot->treeHeight;
}

void Node::RecalculateTreeHeight()
{
    unsigned char leftSubtreeHeight = GetTreeHeight(leftSubtree);
    unsigned char rightSubtreeHeight = GetTreeHeight(rightSubtree);
    treeHeight = 1 + (leftSubtreeHeight > rightSubtreeHeight ? leftSubtreeHeight : rightSubtreeHeight);
}

Node* Node::RotateToRight()
{
    Node* newRoot = leftSubtree;

    leftSubtree = newRoot->rightSubtree;
    newRoot->rightSubtree = this;
    RecalculateTreeHeight();
    newRoot->RecalculateTreeHeight();

    return newRoot;
}

Node* Node::RotateToLeft()
{
    Node* newRoot = rightSubtree;

    rightSubtree = newRoot->leftSubtree;
    newRoot->leftSubtree = this;
    RecalculateTreeHeight();
    newRoot->RecalculateTreeHeight();

    return newRoot;
}
