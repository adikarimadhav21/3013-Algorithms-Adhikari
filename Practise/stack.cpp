#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int x)
    {
        data = x;
        next = nullptr;
    }
};

class Stack
{
private:
    Node *root, *tail;

public:
    Stack()
    {
        root = tail = nullptr;
    }
    void push(int x)
    {
        Node *new_node = new Node(x);
        if (tail == nullptr)
        {
            root = tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
            //        new_node->next = root;
            // root = new_node;
        }
    }

    void pop()
    {
        // LIFO

        Node *end = root;
        Node *prev = nullptr;
        while (end->next != nullptr)
        {
            prev = end;
            end = end->next;
        }
        prev->next = nullptr;

        free(end);
    }
    void print()
    {
        while (root != NULL)
        {
            cout << root->data << " ";
            root = root->next;
        }
        cout << endl;
    }
};

int main()
{
    Stack s;
    s.push(5);
    s.push(2);
    s.push(10);
    s.push(1);
    // s.print();
    s.pop();
    //   s.push(3);

    s.print();
}