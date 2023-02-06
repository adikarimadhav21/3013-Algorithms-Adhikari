#include <iostream>
#include <string>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;
    int avlValue;
    Node(int key)
    {
        data = key;
        left = right = parent = nullptr;
        avlValue = 0;
    
}
};

    class AVLTree
    {
    private:
        Node *root;
        bool rightHeavy(Node *);
        bool leftHeavy(Node *);
       void insert(Node *&, Node *&);
        Node *remove(Node *&, int);
        int height(Node *);
        void computeAVLvalues(Node *&);
        int avlvalues(Node *);
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void printNode(Node *, string);
        void inorder(Node *);

    public:
        AVLTree();

        void insert(int);
        void remove(int num)
        {
            root = remove(root, num);
        }
        bool search(int);
        int treeHeight();
        void printValues();
    };
