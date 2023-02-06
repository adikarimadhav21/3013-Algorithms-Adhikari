#include <iostream>
using namespace std;

struct Node{
    public:

    int data;
    Node *next;
};

void append( Node * &head, int data){
Node * temp=new Node();
temp->data=data;
temp->next=nullptr;
Node * tail=head;
if(head==NULL){
    head=temp;
    return;
}
while(tail->next!=NULL){
    tail=tail->next;

}
tail->next=temp;

}
void push(Node *&head,int data){
    Node *temp=new Node();
    temp->data=data;
    temp->next=head;
    head=temp;
}

void printValue(Node *node){
    while(node !=NULL){
        cout<< node->data <<" ";
        node=node->next;
    }
}
int main(){
Node *head=nullptr;
append(head,5);
append(head,6);
append(head,7);
push(head,4);
push(head,2);
printValue(head);

}