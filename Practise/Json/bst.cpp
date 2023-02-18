#include <iostream>
#include "bst.h"
#include <algorithm>
#include <map>


using namespace std;
BST::BST()
{
}

 Node* BST::Insert1(Node *root, int x, string lname, string fname)
{
    if (!root)
    {
        root = new Node(x, lname, fname);
        return root;
    }
    if (x < root->data)
    {
        root->left=Insert1(root->left, x, lname, fname);
    }
    else
    {
        root->right=Insert1(root->right, x, lname, fname);
    }
    return root;
}

Node* BST::Insert(Node *root, int x, string lname, string fname)
{
    
    if (!root)
    {
        root = new Node(x, lname, fname);
        return root;
    }
    if ( root->last_name.compare(lname) > 0)
    {
        root->left=Insert(root->left, x, lname, fname);
    }
    else
    {
       root->right= Insert(root->right, x, lname, fname);
    }
    return root;
}
// void BST::Insert(Node *&root, int x, string lname, string fname)
//  { 
//        // map<int, Record> records;

//     Insert1(root, x, lname, fname);
//     Insert(root, x, lname, fname);
    
    
//  }

// void BST::Print(Node *root) { Print(root); }

void BST::Print(Node *root)
{
    if (!root)
    {
        return;
    }

    // preorder
    Print(root->left);
    // inorder
    cout << root->data << " " << root->last_name << " " << root->first_name << " ";
    Print(root->right);
    // postorder
}
// Node *BST::Search(Node *root,int key)
// {
//     return Search(root, key);
// }
Node *BST::Search(Node *node, int key)
{
    cout<< " inside search " << endl ;
    if (node == nullptr || node->data == key)
    {
        return node;
    }
    if (key < node->data)
    {
        return Search(node->left, key);
    }
    else
    {
        return Search(node->right, key);
    }
}

// Node *BST::Search(Node *root,string key)
// {
//     return Search(root, key);
// }
int case_insensitive_match(string s1, string s2) {
   //convert s1 and s2 into lower case strings
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings are same
   return 0; //not matched
}
Node *BST::Search(Node *node, string key)

{
    cout<< "case_insensitive_match(node->last_name, key)"  <<case_insensitive_match(node->last_name, key) <<endl;
    if (node == nullptr || case_insensitive_match(node->last_name, key)==1)
    {
        return node;
    }
    if ( node->last_name.compare(key) > 0)
    {
        return Search(node->left, key);
    }
    else
    {
        return Search(node->right, key);
    }
}
