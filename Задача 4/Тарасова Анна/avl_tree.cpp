#include <iostream>

using namespace std;

struct Node
{
    int key;
    unsigned char height;
    Node *left;
    Node *right;
    Node(int k)
    {
        key = k;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AVLTree
{
    Node *root;

    unsigned char height(Node *p)
    {
        return p ? p->height : 0;
    }

    int getBalanceFactor(Node *p)
    {
        return height(p->right) - height(p->left);
    }

    void countNewHeight(Node *p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    Node *rotateRight(Node *p)
    {
        Node *q = p->left;
        p->left = q->right;
        q->right = p;
        countNewHeight(p);
        countNewHeight(q);
        return q;
    }

    Node *rotateLeft(Node *q)
    {
        Node *p = q->right;
        q->right = p->left;
        p->left = q;
        countNewHeight(q);
        countNewHeight(p);
        return p;
    }

    Node *balance(Node *p)
    {
        countNewHeight(p);
        if (getBalanceFactor(p) == 2)
        {
            if (getBalanceFactor(p->right) < 0)
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if (getBalanceFactor(p) == -2)
        {
            if (getBalanceFactor(p->left) > 0)
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p;
    }

    Node *insert(Node *p, int k)
    {
        if (!p)

            return new Node(k);

        if (k < p->key)
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);
        return balance(p);
    }

    Node *findMin(Node *p)
    {
        return p->left ? findMin(p->left) : p;
    }

    Node *removeMin(Node *p)
    {
        if (p->left == 0)
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }

    Node *remove(Node *p, int k)
    {
        if (!p)
            return 0;
        if (k < p->key)
            p->left = remove(p->left, k);
        else if (k > p->key)
            p->right = remove(p->right, k);
        else
        {
            Node *q = p->left;
            Node *r = p->right;
            delete p;
            if (!r)
                return q;
            Node *min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

    void printTree(Node *node, int indent)
    {
        if (node == NULL)
            return;

        for (int i = 0; i < indent; i++)
        {
            printf(" ");
        }
        printf("%d\n", node->key);

        if (node->left != NULL)
        {
            printTree(node->left, indent + 2);
        }
        if (node->right != NULL)
        {
            printTree(node->right, indent + 2);
        }
    }

public:

    AVLTree()
    {
        root = NULL;
    }
    
    void printTree()
    {
        printTree(root, 0);
    }

    void insert(int k)
    {
        root = insert(root, k);
    }

    void remove(int k)
    {
        root = remove(root, k);
    }

    void balance()
    {
        root = balance(root);
    }
};

int main()
{
    AVLTree tree;
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(3);
    tree.insert(4);

    cout << "\nInsert 1 3 4 5 6. Tree:" << endl;
    tree.printTree();

    cout << "\nRemove leaf, 1. Tree:" << endl;
    tree.remove(1);
    tree.printTree();

    cout << "\nInsert 10. Tree:" << endl;
    tree.insert(10);
    tree.printTree();

    cout << "\nRemove root, 5. Tree:" << endl;
    tree.remove(5);
    tree.printTree();

    return 0;
}