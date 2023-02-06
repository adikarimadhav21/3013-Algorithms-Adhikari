#include <iostream>
#include "avlTree.h"
#include <string>
using namespace std;

AVLTree::AVLTree()
{
    root = nullptr;
}
void AVLTree ::insert(Node *&nodePtr, Node *&newNode)
{
    if (nodePtr == NULL)
    {
        nodePtr = newNode;
    }
    else if (newNode->data <= nodePtr->data)
    {
        newNode->parent = nodePtr;
        insert(nodePtr->left, newNode);
    }
    else
    {
        newNode->parent = nodePtr;
        insert(nodePtr->right, newNode);
    }
}
void AVLTree::insert(int value)
{
   // cout << value;
    Node *newNode = new Node(value);
    insert(root, newNode);
    computeAVLvalues(root);
}
void AVLTree ::computeAVLvalues(Node *&nodePtr)
{
    if (nodePtr)
    {
        computeAVLvalues(nodePtr->left);
        computeAVLvalues(nodePtr->right);
        nodePtr->avlValue = avlvalues(nodePtr);
        if (nodePtr->avlValue > 1)
        {
            rotateLeft(nodePtr);
        }
        else if (nodePtr->avlValue < -1)
        {
            rotateRight(nodePtr);
        }
    }
}

int AVLTree::avlvalues(Node *nodePtr)
{
    return height(nodePtr->right) - height(nodePtr->left);
}
int AVLTree::height(Node *ptrNode)
{
    if (ptrNode == NULL)
        return 0;
    else
    {
        return 1 + max(height(ptrNode->left), height(ptrNode->right));
    }
}

void AVLTree::rotateLeft(Node *&subRoot)
{

    if (leftHeavy(subRoot->right))
    {
        rotateRight(subRoot->right);
    }
    Node *temp;
    temp = subRoot->right;
    subRoot->right = temp->left;
    temp->left = subRoot;
    subRoot = temp;
    computeAVLvalues(subRoot);
}

void AVLTree::rotateRight(Node *&subRoot)
{

    if (rightHeavy(subRoot->left))
    {
        rotateRight(subRoot->left);
    }
    Node *temp;
    temp = subRoot->left;
    subRoot->left = temp->right;
    temp->right = subRoot;
    subRoot = temp;
    computeAVLvalues(subRoot);
}
bool AVLTree::leftHeavy(Node *nodePtr)
{
    return height(nodePtr->left) > height(nodePtr->right);
}

bool AVLTree::rightHeavy(Node *nodePtr)
{
    return height(nodePtr->right) > height(nodePtr->left);
}
void AVLTree::inorder(Node *nodePtr){
	if(nodePtr){
		inorder(nodePtr->left);
		cout<<nodePtr->data<<" "<<"("<<nodePtr->avlValue<<") ";
		inorder(nodePtr->right);
	}
    
}
void AVLTree:: printValues(){
    inorder(root);
        
    }