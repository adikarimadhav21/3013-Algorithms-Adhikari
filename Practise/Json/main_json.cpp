#include "json.hpp"
#include <fstream>
#include <iostream>
#include "bst.h"
#include <string>
#include <map>

using namespace std;
using namespace nlohmann;
// using namespace string;
//  using json = nlohmann::json;

/*
int id
string first_name
string last_name
string email
string address
string city
string state
double latitude
double longitude
string car
string car_model
string car_color
string pet
string job_title
string phone_number
vector <string> stocks

*/
/**
 * cd Practise\Json
 * g++ -c  main_json.cpp
 * g++ -c  bst.cpp
 * g++ -o main main_json.o bst.o
 * ./main
 */

void print(Node *result)
{
    if (!result)
    {
        return;
    }

    print(result->left);
    cout << result->data << " " << result->last_name << " " << result->first_name << endl;
    print(result->right);
}
int main()
{
    BST tree;
    //   tree.Insert(6);
    //   tree.Insert(4);
    //   tree.Insert(7);
    //   tree.Insert(2);
    //   tree.Insert(9);
    //   tree.Print();
    Node *root = nullptr;
    Node *root1 = nullptr;
    map<string, Node *> bstMap;
    map<string, string> mapdata;
    mapdata["1"] = "id";
    mapdata["2"] = "last_name";

    ifstream inputfile("data/random_person_data_1.json");
    if (!inputfile.is_open())
    {
        cout << "Error to open files" << endl;
    }
    // json j;
    //  i >> j;
    //    std::string jsonString((std::istreambuf_iterator<char>(inputfile)), std::istreambuf_iterator<char>());

    json jsonData = json::parse(inputfile);

    for (auto item : jsonData.items())
    {
        std::cout << item.key() << " :: " << item.value() << "\n";
        int id;
        string lname;
        string fname;
        for (const auto &value2 : item.value().items())
        {

            if (value2.key() == "id")
            {
                id = value2.value().get<int>();
            }

            if (value2.key() == "first_name")
            {
                fname = value2.value().get<string>();
            }
            if (value2.key() == "last_name")
            {
                lname = value2.value().get<string>();
            }

            cout << value2.key() << " : " << value2.value() << "\n";
        }
     
        root = tree.Insert(root, id, lname, fname);
        root1 = tree.Insert1(root1, id, lname, fname);
        // todo first one insert and search  dynamic method
        // dynamic multiple bst create
        // todo create abstract

        //I'm sorry, but it's not possible to create different binary trees
        // for different elements using a single insert method, as each binary
        // tree must have a unique root node and structure. 
        //To store each element in a separate binary tree, you would need to create a separate insert method for each element,
        // such as an insertID method for storing the "id" element, an insertFirstName method for storing the "first_name" element, and so on.
    }
    bstMap["last_name"] = root;
    bstMap["id"] = root1;

    for (const auto &[key, value] : bstMap)
    {
        tree.Print(value);
        cout << endl;
    }
    string key;
    string data;
    int integer;
 

    while (true)
    {
        cout << "Choose search option :" << endl;
        cout << "1. id " << endl;
        cout << "2. last_name " << endl;
        cout << "3. exit " << endl;
        cin >> key;
        if (key == "3")
        {
            break;
        }
        cout << "Enter value to search " << endl;
        cin >> data;
        if (mapdata[key] == "id")
        {
            int value = stoi(data);
            print(tree.Search(bstMap[mapdata[key]], value));
        }
        else
        {
            print(tree.Search(bstMap[mapdata[key]], data));
        }

        cout << endl;
    }

    // for (const auto &[key, value] : bstMap)
    // {

    //     print(tree.Search(value, data));
    //     cout << endl;
    // }

    // cout << endl;
    // Node *result1 = tree.Search(root, "Galvin");
    // print(result1);
    // cout << endl;
    // Node *result = tree.Search(root1, 3);
    // print(result);
}