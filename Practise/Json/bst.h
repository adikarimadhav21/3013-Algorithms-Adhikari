#include <iostream>
#include <map>

using namespace std;

struct Node
{
    int data;
     string first_name;
     string last_name;
    string email;
    string address;
    string city;
    string state;
    double latitude;
    double longitude;
    string car;
    string car_model;
    string car_color;
    string favorite_movie;
    string pet;
    string job_title;
    string phone_number;
    Node *left;
    Node *right;
    Node(int d,string lname,string fname)
    {
        data = d;
        first_name=fname;
        last_name=lname;
        left = right = nullptr;
    }
    // Node(string s){
    //     data = INT_MIN;
    //     strValue=s;
    //     left = right = nullptr;
    // }
};

class BST
{
private:
   // Node *root;
    // void Print(Node *);
    // void Insert1(Node *&, int,string,string);
    // void Insert(Node *&, int,string,string);
    // Node *Search(Node *node, int) ;
    // Node *Search(Node *node, string) ;
public:
    BST();
   // BST(Node *);
    Node* Insert(Node *,int,string,string);
    Node* Insert1(Node *,int,string,string );
    void Print(Node *) ;
    Node *Search(Node *,int) ;
    Node *Search(Node *,string) ;

};
