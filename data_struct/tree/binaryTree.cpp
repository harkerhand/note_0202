#include <bits/stdc++.h>
using namespace std;

template <class T>
class BinaryTree
{
public:
    BinaryTree();
    bool isEmpty();
    BinaryTree(BinaryTree<T> &bt1, T &item, BinaryTree<T> &bt2);
    BinaryTree<T> *LeftSubStree();
    BinaryTree<T> *RightSubStree();
    T RootData();
};