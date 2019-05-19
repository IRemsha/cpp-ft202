#ifndef AVLTREE_NODE_H
#define AVLTREE_NODE_H


struct Node
{
    explicit Node(int key);
    int key;
    unsigned char treeHeight;
    Node* leftSubtree;
    Node* rightSubtree;

    static unsigned char GetTreeHeight(Node* treeRoot);
    void RecalculateTreeHeight();
    Node* RotateToRight();
    Node* RotateToLeft();
};


#endif //AVLTREE_NODE_H
