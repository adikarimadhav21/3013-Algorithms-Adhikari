#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  Node(int d) {
    data = d;
    left = right = nullptr;
  }
};

class BST {
  Node *root;

  void Print(Node *root) {
    if (!root) {
      return;
    }

    // preorder
    Print(root->left);
    // inorder
    cout << root->data << " ";
    Print(root->right);
    // postorder
  }

  void Insert(Node *&root, int x) {
    if (!root) {
      root = new Node(x);
      return;
    }
    if (x < root->data) {
      Insert(root->left, x);
    } else {
      Insert(root->right, x);
    }
  }
  Node * removeHelper(Node *root, int data){
    if(root==nullptr){
      return nullptr;
    }
    else if (data<root->data){
      root->left=removeHelper(root->left,data);
    }
    else if (data>root->data){
      root->right=removeHelper(root->right,data);
    }
    else
    {
      if(root->left==nullptr && root->right==nullptr)
      {
        delete root;
        return nullptr;
      }
      else if(root->left==nullptr) {
        Node * temp=root->right;
        delete root;

      }
      else if(root->right==nullptr) {
        Node * temp=root->left;
        delete root;
      }
      else  {
        Node *minnode=findMinNode(root->right);
        root->data=minnode->data;
        root->right=removeHelper(root->right,minnode->data);

      }
    }
    return root;
    
  }
  Node * findMinNode(Node * node){
     while(node->left!=nullptr){
      node=node->left;
     }
     return node;
  }

  int Find(Node *root, int key) {
    
    static int count = 0;

    count++;
    if (!root) {
      return count;
    }
    
    if(root->data == key){
      return count;
    }else if(key < root->data){
      return Find(root->left,key);
    }else{
      return Find(root->right,key);
    }
  }

public:
  BST() { root = nullptr; }

  void Insert(int x) { Insert(root, x); }

  void Print() { Print(root); }

  int Find(int key) { return Find(root, key); }
  void remove(int key){
    root=removeHelper(root,key);
  }
};

int main() {
  BST tree;
  tree.Insert(6);
  tree.Insert(4);
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(9);
  tree.remove(2);

//   for (int i = 0; i < 1024; i++) {
//     tree.Insert(rand());
//   }
  tree.Print();
  cout<<tree.Find(10901063)<<endl;
}