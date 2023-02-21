#include <vector>
#include <typeinfo>
#include "bst.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
using namespace std;
using namespace nlohmann;

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}
template <typename T>
void BinarySearchTree<T>::insert(Node *&node, const T &value, int id, string first_name, string last_name, string email, string address, string city, string state, string car,
                                 string car_model, string car_color, string favorite_movie, string pet, string job_title, string phone_number, double latitude, double longitude, vector<string> stocks)
{

    if (node == nullptr)
    {
        node = new Node(value, id, first_name, last_name, email, address, city, state, car,
                        car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        return;
    }
    // C++ compilier will dynamically switch < operator as per data types
    //  todo ignore case sensitive during string compare
    if (value < node->value)
    {
        insert(node->left, value, id, first_name, last_name, email, address, city, state, car,
               car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
    }
    else
    {
        insert(node->right, value, id, first_name, last_name, email, address, city, state, car,
               car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
    }
    
}


template <typename T>
void BinarySearchTree<T>::insert(const T &value, int id, string first_name, string last_name, string email, string address, string city, string state, string car,
                                 string car_model, string car_color, string favorite_movie, string pet, string job_title, string phone_number, double latitude, double longitude, vector<string> stocks)
{

    insert(root, value, id, first_name, last_name, email, address, city, state, car,
           car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
}


template <typename T>
Node* BinarySearchTree<T>::search(Node *node, const T &value) const
{
    if (node == nullptr)
    {
        return node;
    }
    // C++ compilier will dynamically switch < operator as per data types
    //  todo ignore case sensitive during string compare
    if (node->value == value)
    {
        return node;
    }
    else if (value < node->value)
    {
        return search(node->left, value);
    }
    else
    {
        return search(node->right, value);
    }
}
template <typename T>
void BinarySearchTree<T>::print(Node *node)
{
    if (!node)
    {
        return;
    }
    print(node->left);
    // constexpr will check the template parameter T to determine how to print the values during traversal.

    if constexpr (is_same_v<T, GPS>)
    {
        cout << "(" << node->value.lat << ", " << node->value.lon << ") ";
    }
    else
    {
        cout << node->value << " ";
    }

    print(node->right);
}



template <typename T>
Node *BinarySearchTree<T>::search(const T &value) const
{
    return search(root, value);
}
template <typename T>
void BinarySearchTree<T>::print()
{
    print(root);
}
// print the found json  if search values is found
template <typename T>
void BinarySearchTree<T>::printSearch(Node *result)

{
    if (result == nullptr)
    {
        cout << "No record found";
    }
    else
    {
        json nodeJson;
        nodeJson["id"] = result->id;
        nodeJson["first_name"] = result->first_name;
        nodeJson["last_name"] = result->last_name;
        nodeJson["email"] = result->email;
        nodeJson["address"] = result->address;
        nodeJson["city"] = result->city;
        nodeJson["car"] = result->car;
        nodeJson["car_model"] = result->car_model;
        nodeJson["car_color"] = result->car_color;
        nodeJson["favorite_movie"] = result->favorite_movie;
        nodeJson["pet"] = result->pet;
        nodeJson["job_title"] = result->job_title;
        nodeJson["phone_number"] = result->phone_number;
        nodeJson["latitude"] = result->latitude;
        nodeJson["longitude"] = result->longitude;
        nodeJson["stocks"] = result->stocks;

        if constexpr (is_same_v<T, GPS>)
        {
            cout << "Record found for ";
            cout << "(" << result->value.lat << ", " << result->value.lon << ") => ";
        }
        else
        {
            cout << "Record found for " << result->value << "=> " << endl;
        }
        cout << nodeJson;
        cout << endl;
    }
}
