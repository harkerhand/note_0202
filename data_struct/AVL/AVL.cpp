#include <bits/stdc++.h>
using namespace std;

template <typename K, typename E>
class AVL
{
private:
    struct Node
    {
        Node *left, *right;
        K key;
        E element;
        int deltaHeight;
        Node(K key, E element) : key(key), element(element), left(nullptr), right(nullptr), deltaHeight(0) {}
    };
    Node *root = nullptr;

public:
    void insert(K key, E element)
    {
        if (!root)
        {
            root = new Node(key, element);
            return;
        }

        Node *a, *parentA, *p, *parentP;
        a = parentA = p = parentP = nullptr;
        a = p = root;
        while (p)
        {
            if (abs(p->deltaHeight))
            {
                a = p;
                parentA = parentP;
            }
            if (p->key > key)
            {
                parentP = p;
                p = p->left;
            }
            else if (p->key < key)
            {
                parentP = p;
                p = p->right;
            }
            else
            {
                p->element = element;
                return;
            }
        }

        Node *newNode = new Node(key, element);
        if (parentP->key > key)
            parentP->left = newNode;
        else
            parentP->right = newNode;

        int tmpDeltaHeight;
        Node *b, *c;
        if (a->key > key)
        {
            b = p = a->left;
            tmpDeltaHeight = 1;
        }
        else
        {
            b = p = a->right;
            tmpDeltaHeight = -1;
        }
        while (p != newNode)
        {
            if (p->key > key)
            {
                p->deltaHeight = 1;
                p = p->left;
            }
            else
            {
                p->deltaHeight = -1;
                p = p->right;
            }
        }

        if (a->deltaHeight == 0 || a->deltaHeight == -tmpDeltaHeight)
        {
            a->deltaHeight += tmpDeltaHeight;
            return;
        }

        if (tmpDeltaHeight == 1)
        {
            if (b->deltaHeight == 1) // LL
            {
                a->left = b->right;
                b->right = a;
                a->deltaHeight = b->deltaHeight = 0;
            }
            else // LR
            {
                c = b->right;
                b->right = c->left;
                a->left = c->right;
                c->left = b;
                c->right = a;
                switch (c->deltaHeight)
                {
                case 1:
                    a->deltaHeight = -1;
                    b->deltaHeight = 0;
                    break;
                case -1:
                    a->deltaHeight = 0;
                    b->deltaHeight = 1;
                    break;
                case 0:
                    a->deltaHeight = b->deltaHeight = 0;
                    break;
                }
                c->deltaHeight = 0;
                b = c;
            }
        }
        else
        {
            if (b->deltaHeight == -1) // RR
            {
                a->right = b->left;
                b->left = a;
                a->deltaHeight = b->deltaHeight = 0;
            }
            else // RL
            {
                c = b->left;
                b->left = c->right;
                a->right = c->left;
                c->right = b;
                c->left = a;
                switch (c->deltaHeight)
                {
                case 1:
                    a->deltaHeight = 0;
                    b->deltaHeight = -1;
                    break;
                case -1:
                    a->deltaHeight = 1;
                    b->deltaHeight = 0;
                    break;
                case 0:
                    a->deltaHeight = b->deltaHeight = 0;
                    break;
                }
                c->deltaHeight = 0;
                b = c;
            }
        }
        if (!parentA)
            root = b;
        else if (a == parentA->left)
            parentA->left = b;
        else
            parentA->right = b;
    }

    void print()
    {
        queue<Node *> q;
        q.push(root);
        int index = 100;
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();
            cout << node->key << " ";
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }
};

signed main()
{
    AVL<int, int> avl;
    for (int i = 1; i < 50; i++)
        avl.insert(i, i);

    avl.print();
}