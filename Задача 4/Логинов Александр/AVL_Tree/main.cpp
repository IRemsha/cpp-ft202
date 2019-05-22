#include <iostream>
#include <algorithm>

using namespace std;

template <class V>
struct Node
{
    Node<V>* Left;
    Node<V>* Right;
    V Value;
    int Height;

    Node(V value)
    {
        Left = Right = nullptr;
        Value = value;
        Height = 1;
    }
};

template <class V>
class AVL_Tree
{
    Node<V>* root;


    int _get_height(Node<V> *tree)
    {
        if (tree)
            return tree->Height;
        return 0;
    }

    int _get_difference_subtrees_height(Node<V> *tree)
    {
        return _get_height(tree->Left) - _get_height(tree->Right);
    }

    void _update_height(Node<V> *tree)
    {
        tree->Height = max(_get_height(tree->Left), _get_height(tree->Right)) + 1;
    }

    Node<V>*  _balance(Node<V> *tree)
    {
        _update_height(tree);
        if (_get_difference_subtrees_height(tree) == -2)
        {
            if(_get_difference_subtrees_height(tree->Right) > 0)
                tree->Right = _r_rotate(tree->Right);
            return _l_rotate(tree);
        }
        if (_get_difference_subtrees_height(tree) == 2)
        {
            if (_get_difference_subtrees_height(tree->Left) < 0)
                tree->Left = _l_rotate(tree->Left);
            return _r_rotate(tree);
        }
        return tree;
    }

    Node<V>* _r_rotate(Node<V> *tree)
    {
        auto L = tree->Left;
        tree->Left = L->Right;
        L->Right = tree;
        tree->Height = max(_get_height(tree->Left), _get_height(tree->Right)) + 1;
        L->Height = max(_get_height(L->Left), _get_height(tree)) + 1;
        return L;
    }

    Node<V>* _l_rotate(Node<V> *tree)
    {
        auto R = tree->Right;
        tree->Right = R->Left;
        R->Left = tree;
        tree->Height = max(_get_height(tree->Left), _get_height(tree->Right)) + 1;
        R->Height = max(_get_height(R->Right), _get_height(tree)) + 1;
        return R;
    }

    Node<V>* _add(Node<V> *tree, V value)
    {
        if (!tree)
            return new Node<V>(value);
        if (value < tree->Value)
            tree->Left = _add(tree->Left, value);
        else
            tree->Right = _add(tree->Right, value);
        tree->Height = max(_get_height(tree->Right), _get_height(tree->Left)) + 1;
        return _balance(tree);

    }

    void _print(Node<V>* tree, int level=0)
    {
        if (!tree)
            return;
        _print(tree->Left, level+1);
        for(int i = 0; i < level * 10; i++ )
            cout << " ";
        cout << tree->Value << endl << endl;
        _print(tree->Right, level+ 1);
    }

    Node<V>* _getMinNode(Node<V> *tree)
    {
        auto node = tree;
        while (node->Left)
            node = node->Left;
        return node;
    }

    Node<V>* _delete(V value, Node<V>* tree)
    {
        if (!tree)
            return tree;
        if (value < tree->Value) {
            tree->Left = _delete(value, tree->Left);
        }
        else if (value > tree->Value){
            tree->Right = _delete(value, tree->Right);
        }
        else
        {
            if (tree->Left && tree->Right)
            {
                auto node = _getMinNode(tree->Right);
                tree->Value = node->Value;
                tree->Right = _delete(node->Value, tree->Right);
                return _balance(tree);
            }
            else if (tree->Left)
                return tree->Left;
            else if (tree->Right)
                return tree->Right;
            return NULL;
        }
        return _balance(tree);

    }

public:


    AVL_Tree(V value)
    {
        root = new Node<V>(value);
    }

    void Add(V value)
    {
         root = _add(root, value);
    }

    void Balance()
    {
        root = _balance(root);
    }

    void Delete(V value)
    {
        auto tree = _delete(value, root);
        root->Value = tree->Value;
        root->Left = tree->Left;
        root->Right = tree->Right;
    }
    void print()
    {
        cout << "TREE: " << endl;
        _print(root);
    }


};

void simpleTestAdd()
{
    cout << "____________TEST ADD____________" << endl;
    auto tree = new AVL_Tree<int>(2);
    tree->print();
    tree->Add(100500);
    cout << "Add 100500" << endl;
    tree->print();
    tree->Add(-10);
    cout << "Add -10" << endl;
    tree->print();
    tree->Add(999999);
    cout << "Add 999999" << endl;
    tree->print();
    delete tree;
}

void simpleTestRemove()
{
    cout << "____________TEST DELETE____________" << endl;
    auto tree = new AVL_Tree<int>(2);
    tree->Add(10);
    tree->Add(-2);
    tree->print();
    cout << "Delete 2" << endl;
    tree->Delete(2);
    tree->print();
}

void balancingTestAfterAdding()
{
    cout << "____________BALANCING TEST AFTER ADDING____________" << endl;
    auto tree = new AVL_Tree<int>(1);
    tree->print();
    cout << "ADD 2" << endl;
    tree->Add(2);
    tree->print();
    cout << "ADD 3" << endl;
    tree->Add(3);
    tree->print();
    cout << "ADD 4" << endl;
    tree->Add(4);
    tree->print();
    cout << "ADD 5" << endl;
    tree->Add(5);
    tree->print();
    cout << "ADD 6" << endl;
    tree->Add(6);
    tree->print();
    delete tree;
}

void testWithString()
{
    cout << "____________TEST STRING____________" << endl;
    auto tree = new AVL_Tree<string>("bla");
    tree->print();
    cout << "Add 'foo'" << endl;
    tree->Add("foo");
    tree->print();
    cout << "Add 'aa'" << endl;
    tree->Add("aa");
    tree->print();
    delete tree;
}

int main() {
    simpleTestAdd();
    simpleTestRemove();
    balancingTestAfterAdding();
    testWithString();
    return 0;
}