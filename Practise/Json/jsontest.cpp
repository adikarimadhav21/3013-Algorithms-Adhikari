#include <iostream>
#include <fstream>
#include "json.hpp"

template<typename T>
struct Node {
    std::pair<double, double> gps;
    T value;
    Node<T>* left;
    Node<T>* right;
    
    Node(std::pair<double, double> gps, T value) {
        this->gps = gps;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template<typename T>
void insert(Node<T>*& root, std::pair<double, double> gps, T value) {
    if (root == nullptr) {
        root = new Node<T>(gps, value);
    } else if (gps.first < root->gps.first) {
        insert(root->left, gps, value);
    } else if (gps.first > root->gps.first) {
        insert(root->right, gps, value);
    } else if (gps.second < root->gps.second) {
        insert(root->left, gps, value);
    } else if (gps.second > root->gps.second) {
        insert(root->right, gps, value);
    }
}



template<typename T>
T search(Node<T>* root, std::pair<double, double> gps) {
    while (root != nullptr) {
        if (gps.first == root->gps.first && gps.second == root->gps.second) {
            return root->value;
        } else if (gps.first < root->gps.first || (gps.first == root->gps.first && gps.second < root->gps.second)) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return T();
}
template<typename T>
 void print(Node<T>* node)
    {
        if (!node)
        {
            return;
        }
        print(node->left);
      
       // std::cout << node->value << " ";
        std::cout << node->gps.first << " " <<node->gps.first;

        print(node->right);
    }

int main() {
    std::ifstream input_file("gps.json");
    nlohmann::json json_data;
    input_file >> json_data;
    
    Node<int>* root = nullptr;
    for (const auto& item : json_data) {
        double latitude = item["latitude"];
        double longitude = item["longitude"];
        int value = item["value"];
        insert(root, std::make_pair(latitude, longitude), value);
    }
    
    std::pair<double, double> search_gps = std::make_pair(42.3601, -71.0589);
    int search_result = search(root, search_gps);
    if (search_result != -1) {
        std::cout << "Found value: " << search_result << std::endl;
    } else {
        std::cout << "GPS not found" << std::endl;
    }
    print(root);
    
    return 0;
}
