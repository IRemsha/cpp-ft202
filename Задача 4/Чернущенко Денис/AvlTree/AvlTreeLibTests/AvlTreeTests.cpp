#include "gtest/gtest.h"
#include "../AvlTreeLib/AvlTree.h"
#include <ctime>

#define PRINT_TREE

using namespace std;

vector<int> GetRandomVector()
{
    srand(time(nullptr));
    vector<int> resultArray = vector<int>(rand() % 100 + 1);
    for (int & i : resultArray)
        i = (rand() % 100);

    return resultArray;
}

TEST(AvlTree, InsertOneKey)
{
    auto tree = AvlTree();

    tree.Insert(5);

    ASSERT_EQ(tree.GetKeys().size(), 1);
    ASSERT_EQ(tree.GetKeys()[0], 5);

#ifdef PRINT_TREE
    tree.PrintTree();
#endif
}

TEST(AvlTree, CreateSimpleTree)
{
    auto tree = AvlTree();

    for (int key : {1, 2, 3, 4, 5})
        tree.Insert(key);

#ifdef PRINT_TREE
    tree.PrintTree();
#endif
}

TEST(AvlTree, InsertAndReturnRandomVector)
{
    auto tree = AvlTree();

    vector<int> vector = GetRandomVector();

    for (int i : vector)
        tree.Insert(i);

    sort(vector.begin(), vector.end());

    ASSERT_EQ(tree.GetKeys(), vector);

#ifdef PRINT_TREE
    tree.PrintTree();
#endif
}

TEST(AvlTree, RemoveSomeKeys)
{
    auto tree = AvlTree();

    for (int key : { 1, 8, 4, 2, 7, 10, 3 })
        tree.Insert(key);

    tree.Remove(8);
    tree.Remove(3);

    ASSERT_EQ(tree.GetKeys(), (vector<int>{ 1, 2, 4, 7, 10 }));

#ifdef PRINT_TREE
    tree.PrintTree();
#endif
}

TEST(AvlTree, RemoveAllKeys)
{
    auto tree = AvlTree();

    vector<int> vector = GetRandomVector();
    for (int i : vector)
        tree.Insert(i);tree.PrintTree();

    random_shuffle(vector.begin(), vector.end());

    for (int key : vector)
        tree.Remove(key);

    vector.clear();

    ASSERT_EQ(tree.GetKeys(), vector);

#ifdef PRINT_TREE
    tree.PrintTree();
#endif
}

TEST(AvlTree, ThrowOnWrongRemove)
{
    auto tree = AvlTree();

    ASSERT_THROW(tree.Remove(0), std::out_of_range);

    tree.Insert(6);

    ASSERT_THROW(tree.Remove(5), std::out_of_range);

#ifdef PRINT_TREE
    tree.PrintTree();
#endif
}
