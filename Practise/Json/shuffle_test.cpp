#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <typeinfo>
#include <map>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

bool containsIgnoreCase(const std::string &str1, const std::string &str2)
{
    auto str1Begin = str1.begin();
    auto str1End = str1.end();
    auto str2Begin = str2.begin();
    auto str2End = str2.end();

    // Convert both strings to lowercase and remove special characters
    std::string str1Lower;
    std::transform(str1Begin, str1End, std::back_inserter(str1Lower), [](char c)
                   { return std::tolower(c); });
    str1Lower.erase(std::remove_if(str1Lower.begin(), str1Lower.end(), [](char c)
                                   { return !std::isalnum(c); }),
                    str1Lower.end());

    std::string str2Lower;
    std::transform(str2Begin, str2End, std::back_inserter(str2Lower), [](char c)
                   { return std::tolower(c); });
    str2Lower.erase(std::remove_if(str2Lower.begin(), str2Lower.end(), [](char c)
                                   { return !std::isalnum(c); }),
                    str2Lower.end());

    // Check if str1Lower contains str2Lower
    return str1Lower.find(str2Lower) != std::string::npos;
}

struct GPS
{
public:
    double lat;
    double lon;

    bool operator==(const GPS &other) const
    {
        return lat == other.lat && lon == other.lon;
    }

    bool operator<(const GPS &other) const
    {
        if (lat == other.lat)
        {
            return lon < other.lon;
        }
        return lat < other.lat;
    }
};
class JsonData
{
public:
    int id;
    string first_name;
    string last_name;
    GPS gps;
};

struct Node
{
    JsonData *data;
    Node *next;
};

class LinkedList
{
public:
    LinkedList()
    {
        head = nullptr;
    }

    void add(JsonData *data)
    {
        Node *node = new Node;
        node->data = data;
        node->next = head;
        head = node;
    }

    enum SearchCriteria
    {
        ID,
        FIRST_NAME,
        LAST_NAME
    };
    JsonData *find(const string &key, SearchCriteria criteria)
    {
        Node *current = head;
        while (current != nullptr)
        {
            switch (criteria)
            {
            case ID:
                if (current->data->id == stoi(key))
                {
                    return current->data;
                }
                break;
            case FIRST_NAME:
                if (containsIgnoreCase(current->data->first_name, key))
                {
                    return current->data;
                }
                break;
            case LAST_NAME:
                if (containsIgnoreCase(current->data->last_name, key))
                {
                    return current->data;
                }
                break;
            }
            current = current->next;
        }
        return nullptr;
    }

    JsonData *find(GPS key)
    {
        Node *current = head;
        while (current != nullptr)
        {

            if (current->data->gps == key)
            {
                return current->data;
            }

            current = current->next;
        }
        return nullptr;
    }

    void seachPrint( JsonData *d){
         if(d!=nullptr){
            cout<< "Found record" << endl;
            cout << d->id << " " <<d->first_name;
         }
         else{
            cout << " No found";
         }
    }

private:
    Node *head;
};

void printTime(auto start)
{
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << std::fixed << std::setprecision(6) << "Record Search time:::: " << elapsed.count() << " seconds\n";
}
int main()
{
     auto start = std::chrono::high_resolution_clock::now();


    // do some work here...
      for (int i=0;i<=5;i++){

      int a=i;
      cout<<a;
               
    }
    printTime(start);

  
     

    return 0;
}
