#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int key)
    {
        data = key;
        left = right = nullptr;
    }
};

class BST
{
    Node *root;
    void print(Node *root)
    {
        if (!root)
        {
            return;
        }
        print(root->left);
        cout << root->data << " ";
        print(root->right);
    }
    int printHeight(Node *root)
    {
        if (!root)
        {
            return 0;
        }
        int l = printHeight(root->left);
        cout << "l data " << root->data << endl;
        cout << "l " << l << endl;

        int r = printHeight(root->right);
        cout << "r data " << r << endl;
        cout << "r " << r << endl;

        return 1 + max(l, r);
    }

public:
    BST()
    {
        root = nullptr;
    }
    void insert()
    {
        root = new Node(15);
        root->left = new Node(10);
        root->right = new Node(20);
        root->left->left = new Node(8);
        root->left->right = new Node(12);
        root->right->left = new Node(16);
        root->right->right = new Node(25);
        root->right->right->right = new Node(26);
    }
    void print()
    {
        print(root);
    }
    int printHeight()
    {
        return printHeight(root);
    }
};

int main()
{
    BST t;
    t.insert();
    t.print();
    cout << endl;
    cout << t.printHeight() << endl;
    cout << "Main Test" << endl;
}