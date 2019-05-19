#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include "Node.h"
#include <vector>
#include <iostream>

class AvlTree
{
public:
    ~AvlTree();

    void Insert(int key);
    void Remove(int key);
    std::vector<int> GetKeys();
    void PrintTree();

private:
    Node* root;

    static char CalculateBalanceFactor(Node* treeRoot);
    static Node* Balance(Node* treeRoot);
    static Node* Insert(Node* treeRoot, int key);
    static Node* FindMinNode(Node* treeRoot);
    static Node* RemoveMinKey(Node* treeRoot);
    static Node* RemoveKey(Node* treeRoot, int removedKey);
    static void TraverseTree(Node* treeRoot, std::vector<int>& vector);
    static void PrintTree(const std::string& prefix, const Node* node, bool isLeft);
};


#endif //AVLTREE_AVLTREE_H
