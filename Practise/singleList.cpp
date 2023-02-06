#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class LinkedList
{
    Node *head;
    Node *tail;

public:
    LinkedList()
    {
        head = tail = nullptr;
    }

    void frontInsert(Node *new_node)
    {
        new_node->next = head;
        head = new_node;
    }

    void tailInsert(Node *new_node)
    {
        tail->next = new_node;
        tail = new_node;
    }

    // add front
    void push(int value)
    {
        Node *temp = new Node(value);
        frontInsert(temp);
    }
    // append

    void append(int value)
    {
        Node *temp = new Node(value);
        if (tail == nullptr)
        {
            head = tail = temp;
        }
        else
        {
            tailInsert(temp);
        }
    }

    void orderInsert(int value)
    {
        Node *temp = new Node(value);
        if (head == nullptr)
        {
            head = tail = temp;
        }
        else if (head->data < temp->data)
        {
            tailInsert(temp);
        }
        else if (head->data > temp->data)
        {
            frontInsert(temp);
        }
        else
        {
            Node *travel = head;
            while (travel->next->data < temp->data)
            {
                travel = travel->next;
            }
            temp->next = travel->next;
            travel->next = temp;
        }
    }
    void printValue()
    {

        while (head != NULL)
        {
            cout << head->data << " ";
            head = head->next;
        }
    }
};

int main()
{
    LinkedList l;
    // l.push(2);
    // l.push(1);
    // l.append(3);
    // l.append(4);
    l.orderInsert(3);
    l.orderInsert(4);
    l.orderInsert(1);
    l.orderInsert(8);
    l.orderInsert(3);
    l.printValue();
}
