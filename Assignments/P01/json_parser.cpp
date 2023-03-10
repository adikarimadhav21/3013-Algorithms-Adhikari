/*****************************************************************************
*
*  Author:           Madhav Adhikari
*  Email:            madhikari0624@my.msutexas.edu
*  Label:            P01
*  Title:            Json File Parser
*  Course:           CMPS 3013
*  Semester:         Spring 2023
*
*  Description:
*        Using Mockaroo, we created random_person_data.json files where Json has 16 elements. This program has binary search tree and a linked list data structure to load data and search the respective data by comparing the time difference between them. This program made the binary search tree/LinkedList for 8 values only ("id";"last_name"; - "email"; - "car_model"; - "job_title"; - "address";- "phone_number - "latitude"; - "GPS";) of the 16 values ( GPS will be used to search data by pairing latitude and longitude) of json files.
*
*  Usage:
*        Parse Json files and search item by comparing time between two data structure BST and linkedList
*
*  Files:
   main.cpp    : driver program
   json.hpp    : header files of nlohmann to read the json files
   banner.txt  : own banner for this program
   random_person_data_1.json : inut data which have Json object
   output_file : screenshot of output
*****************************************************************************/
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
using namespace nlohmann;

/**
 * Public : printTime
 *
 * Description:
 *      Calulcate record search time and display searching time.
 *
 * Params:
 *      [auto]     :  start
 *      [bool]     : flag
 *
 * Returns:
 *      void
 */
void printTime(auto start, bool flag)
{
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << fixed << setprecision(6) << "Record search time:::::: " << elapsed.count() << " seconds\n";
    if (flag)
    {
        cout << "############ Searching end ##################" << endl;
    }
}

/**
 * Public : containsIgnoreCase
 *
 * Description:
 *      Find one string to another string  by ignoring cases and special characters
 *
 * Params:
 *      [String]     :  str1
 *      [String]     :  str2
 *
 * Returns:
 *      bool
 */

bool containsIgnoreCase(const string &str1, const string &str2)
{
    auto str1Begin = str1.begin();
    auto str1End = str1.end();
    auto str2Begin = str2.begin();
    auto str2End = str2.end();

    // Convert both strings to lowercase and remove special characters
    string str1Lower;
    transform(str1Begin, str1End, back_inserter(str1Lower), [](char c)
                   { return tolower(c); });
    str1Lower.erase(remove_if(str1Lower.begin(), str1Lower.end(), [](char c)
                                   { return !isalnum(c); }),
                    str1Lower.end());

    string str2Lower;
    transform(str2Begin, str2End, back_inserter(str2Lower), [](char c)
                   { return tolower(c); });
    str2Lower.erase(remove_if(str2Lower.begin(), str2Lower.end(), [](char c)
                                   { return !isalnum(c); }),
                    str2Lower.end());

    // Check if str1Lower contains str2Lower
    return str1Lower.find(str2Lower) != string::npos;
}

/**
 * Operator overloading to achieve case-insensitive/contains string comparison
 *
 **/

struct WildCardString
{
    string str;
    WildCardString(string value)
    {
        str = value;
    }
    bool operator==(const WildCardString &other) const
    {
        return containsIgnoreCase(str, other.str);
    }

    bool operator<(const WildCardString &other) const
    {
        return lexicographical_compare(
            str.begin(), str.end(),
            other.str.begin(), other.str.end(),
            [](char a, char b)
            {
                return tolower(a) < tolower(b);
            });
    }
};

/**
 * Define the GPS struct with the operator== and operator< functions.
 * operator function can be used later in insert and search function of BST/LinkedListto compare GPS types data
 */

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
/**
 * Define Jsondata class/struct to collect the json elements
 */
class JsonData
{
public:
    int id;
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
    vector<string> stocks;
    GPS gps;
};

/**
 *  define NodeList struct to hold Jsondata in linkedList
 */
struct NodeList
{
    JsonData *data;
    NodeList *next;
};

/**
 * Class LinkedList
 *
 * Description:
 *       This class implements linkedList data structure where JsonData is insert and search accordingly
 *
 * Public Methods:
 *          LinkedList()
 *    void add(JsonData *data)
 *    void append(JsonData *data)
 *    void printCount(string key, int nodeCount)
 *    JsonData *find(const string &key, string criteria)
 *    JsonData *find(GPS key)
 *    void printSearch(JsonData *result)
 *    void printValue()
 *
 * Private Methods:
 *  N/A
 *
 * Usage:
 *  LinkedList()  // create instance of LinkedList
 *  void add(JsonData *data)    // add item on front
 *  void append(JsonData *data)  // add item on tail
 *  void printCount(string key, int nodeCount) // Display number of nodes to search any item
 *  JsonData *find(const string &key, string criteria) // search any item in linkedlist
 *  JsonData *find(GPS key) // search GPS in linkedlist
 *  void printSearch(JsonData *result) // Display found values after searching item
 *  void printValue()  // trasversal linkedList
 */
class LinkedList
{
public:
    LinkedList()
    {
        head = nullptr;
    }
    // add item on front
    void add(JsonData *data)
    {
        NodeList *node = new NodeList;
        node->data = data;
        node->next = head;
        head = node;
    }
    /**
     * Public : append
     *
     * Description:
     *      Add Jsondata in linkedList at the end of list
     *
     * Params:
     *      [JsonData]     :  *data
     *
     * Returns:
     *      void
     */
    void append(JsonData *data)
    {
        NodeList *temp = new NodeList();
        temp->data = data;
        temp->next = nullptr;
        NodeList *tail = head;
        if (head == NULL)
        {
            head = temp;
            return;
        }
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = temp;
    }
    /**
     * Public : printCount
     *
     * Description:
     *      Dsiplay the number of nodes/count to search iteam
     *
     * Params:
     *      [String]     :  key
     *      [int]     :  nodeCount
     *
     * Returns:
     *      void
     */
    void printCount(string key, int nodeCount)
    {
        cout << "Comapared \"" << key << "\"  to " << nodeCount << " nodes" << endl;
    }
    // search values in linked list according to criteria (like id,first_name)
    JsonData *find(const string &key, string criteria)
    {
        int nodeCount = 0; // count number of nodes while searching the values
        NodeList *current = head;
        while (current != nullptr)
        {
            nodeCount++;
            if (criteria == "id")
            {
                if (current->data->id == stoi(key))
                {
                    printCount(key, nodeCount);
                    return current->data;
                }
            }
            else if (criteria == "email")
            {
                if (containsIgnoreCase(current->data->email, key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }
            else if (criteria == "last_name")
            {
                if (containsIgnoreCase(current->data->last_name, key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }
            else if (criteria == "car_model")
            {
                if (containsIgnoreCase(current->data->car_model, key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }
            else if (criteria == "job_title")
            {
                if (containsIgnoreCase(current->data->job_title, key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }
            else if (criteria == "phone_number")
            {
                if (containsIgnoreCase(current->data->phone_number, key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }
            else if (criteria == "address")
            {
                if (containsIgnoreCase(current->data->address, key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }
            else if (criteria == "latitude")
            {
                if (current->data->latitude == stod(key))
                {
                    printCount(key, nodeCount);

                    return current->data;
                }
            }

            current = current->next;
        }
        printCount(key, nodeCount);
        return nullptr;
    }
    // serach GPS in linkedlist
    JsonData *find(GPS key)
    {
        int nodeCount = 0; // count number of nodes while searching the values

        NodeList *current = head;
        while (current != nullptr)
        {
            nodeCount++;

            if (current->data->gps == key)
            {
                cout << "Comapared "
                     << "(" << key.lat << ", " << key.lon << ") "
                     << " to " << nodeCount << " nodes" << endl;
                return current->data;
            }

            current = current->next;
        }
        cout << "Comapared "
             << "(" << key.lat << ", " << key.lon << ") "
             << " to " << nodeCount << " nodes" << endl;
        return nullptr;
    }
    /**
     * Public : printSearch
     *
     * Description:
     *      Dsiplay found item after seaching in the linkedlist
     *
     * Params:
     *      [JsonData]     :  result
     *
     * Returns:
     *      void
     */
    void printSearch(JsonData *result)
    {
        if (result != nullptr)
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
            cout << "Record found => ";
            cout << nodeJson;
            cout << endl;
        }
        else
        {
            cout << "No record found" << endl;
        }
        // cout << "############ Searching end ##################" << endl;
    }
    // print all linkedList values
    void printValue()
    {
        NodeList *travel = head;

        while (travel != NULL)
        {
            cout << travel->data->id << " " << travel->data->first_name;
            travel = travel->next;
        }
    }

private:
    NodeList *head;
};

/**
 * Class BinarySearchTree
 *
 * Description:
            BinarySearchTree class implements binary search tree data structure.
            This class defines dynamic types using a template parameter typename T,
            which allows it to work with any data type
 * Public Methods:
 *          BinarySearchTree()
 *    void insert(const T &value, JsonData jsondata)
 *    Node *search(const T &value) const
 *    void print()
 *    void printSearch(Node *result)
 *
 * Private Methods:
 *  struct Node {}
 *  void insert(Node *&node, const T &value, JsonData jsondata)
 *  Node *search(Node *node, const T &value) const
 *  void print(Node *node)
 *
 * Usage:
 *  BinarySearchTree()  // create instance of BinarySearchTree class
 *  void insert(Node *&node, const T &value, JsonData jsondata)    // add item on BST
 *  Node *search(Node *node, const T &value) const // search any item in BST
 *  JsonData *find(GPS key) // search GPS in linkedlist
 * void print(Node *node) // transversal BST
 * void printSearch(Node *result) // Display found values after searching item
 */

template <typename T>
class BinarySearchTree
{
private:
    struct Node
    {
        T value; // this variable will be used to make binary search tree for different types like int,string ,GPS
        JsonData jsondata;

        Node *left;
        Node *right;

        Node(const T &value, JsonData jsondata)
            : value(value),
              jsondata(jsondata),
              left(nullptr),
              right(nullptr)

        {
        }
    };

    Node *root;

    void insert(Node *&node, const T &value, JsonData jsondata)
    {

        if (node == nullptr)
        {
            node = new Node(value, jsondata);
            return;
        }
        // C++ compilier will dynamically switch < operator as per data types
        //  todo ignore case sensitive during string compare
        if (value < node->value)
        {
            insert(node->left, value, jsondata);
        }
        else
        {
            insert(node->right, value, jsondata);
        }
    }
    /**
     * Private : search
     *
     * Description:
     *      Search item in respective BST
     *
     * Params:
     *      [Node]     :  *node
     *      [T]     :  &value
     *
     * Returns:
     *      Node
     */
    Node *search(Node *node, const T &value) const
    {
        static int count = 0; // count number of nodes while searching the values
        count++;

        if (node == nullptr)
        {
            cout << "Comapared  to " << count << " nodes" << endl;
            count = 0; // static count retain previous values while searching anthor values so  re-initialized

            return node;
        }
        // C++ compilier will dynamically switch < operator as per data types
        if (node->value == value)
        {
            // constexpr will check the template parameter T to determine how to print the values .

            if constexpr (is_same_v<T, GPS>)
            {
                cout << "Comapared "
                     << "(" << value.lat << ", " << value.lon << ") "
                     << " to " << count << " nodes" << endl;
            }
            else if constexpr (is_same_v<T, WildCardString>)
            {
                cout << "Comapared "
                     << "(" << value.str << ") "
                     << " to " << count << " nodes" << endl;
            }
            else
            {
                cout << "Comapared \"" << value << "\"  to " << count << " nodes" << endl;
            }
            count = 0; // static count retain previous values while searching anthor values so  re-initialized

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
    /**
     * Private : print
     *
     * Description:
     *      Transversal BST
     *
     * Params:
     *      [Node]     :  *node
     *
     * Returns:
     *      void
     */
    void print(Node *node)
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
        else if constexpr (is_same_v<T, WildCardString>)
        {
            cout << node->value.str << " ";
        }

        else
        {
            cout << node->value << " ";
        }

        print(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const T &value, JsonData jsondata)
    {

        insert(root, value, jsondata);
    }

    Node *search(const T &value) const
    {

        return search(root, value);
    }
    void print()
    {
        print(root);
    }
    /**
     * Public : printSearch
     *
     * Description:
     *      Dsiplay found json elements in BST
     *
     * Params:
     *      [Node]     :  result
     *
     * Returns:
     *      void
     */
    void printSearch(Node *result)

    {
        if (result == nullptr)
        {
            cout << "No record found" << endl;
            // cout << "############ Searching end ##################" << endl;
        }
        else
        {
            json nodeJson;
            nodeJson["id"] = result->jsondata.id;
            nodeJson["first_name"] = result->jsondata.first_name;
            nodeJson["last_name"] = result->jsondata.last_name;
            nodeJson["email"] = result->jsondata.email;
            nodeJson["address"] = result->jsondata.address;
            nodeJson["city"] = result->jsondata.city;
            nodeJson["car"] = result->jsondata.car;
            nodeJson["car_model"] = result->jsondata.car_model;
            nodeJson["car_color"] = result->jsondata.car_color;
            nodeJson["favorite_movie"] = result->jsondata.favorite_movie;
            nodeJson["pet"] = result->jsondata.pet;
            nodeJson["job_title"] = result->jsondata.job_title;
            nodeJson["phone_number"] = result->jsondata.phone_number;
            nodeJson["latitude"] = result->jsondata.latitude;
            nodeJson["longitude"] = result->jsondata.longitude;
            nodeJson["stocks"] = result->jsondata.stocks;
            // constexpr will check the template parameter T to determine how to print the values .
            if constexpr (is_same_v<T, GPS>)
            {
                cout << "Record found for ";
                cout << "(" << result->value.lat << ", " << result->value.lon << ") => ";
            }
            else if constexpr (is_same_v<T, WildCardString>)
            {
                cout << "Record found for " << result->value.str << "=> ";
            }
            else
            {
                cout << "Record found for " << result->value << "=> ";
            }
            cout << nodeJson;
            cout << endl;
            // cout << "############ Searching end ##################" << endl;
        }
    }
};

int main()
{

    // Declare maps to store the multiples binary search tree where key is string and values is instance of BinarySearchTree
    map<string, BinarySearchTree<int>> bstMapInt;
    map<string, BinarySearchTree<WildCardString>> bstMapString;
    map<string, BinarySearchTree<double>> bstMapDouble;
    map<string, BinarySearchTree<GPS>> bstMapGPS;

    LinkedList l;                  // instance of LinkedList
    double latitude, longitude;    // hold latitude and longitude
    GPS gps;                       // instance of LinkedList
    JsonData jsondata;             // collect json data from files
    vector<JsonData> JsonDataList; // collect multiple JsonData in vector

    // read josn files .

    ifstream inputfile("data/random_person_data_1.json");
    if (!inputfile.is_open())
    {
        cout << "Error to open files" << endl;
    }

    json jsonData = json::parse(inputfile);

    // loop to extract each line of json in files (like NDJson where JSON lines separted by new line character)
    for (auto item : jsonData.items())
    {
        vector<string> stocks;

        //  cout << item.key() << " :: " << item.value() << "\n";

        // iterate for each elements of JSON object
        for (const auto &value : item.value().items())
        {

            if (value.key() == "id")
            {
                jsondata.id = value.value().get<int>();
            }

            else if (value.key() == "first_name")
            {
                jsondata.first_name = value.value().get<string>();
            }
            else if (value.key() == "last_name")
            {
                jsondata.last_name = value.value().get<string>();
            }
            else if (value.key() == "email")
            {
                jsondata.email = value.value().get<string>();
            }
            else if (value.key() == "address")
            {
                jsondata.address = value.value().get<string>();
            }
            else if (value.key() == "city")
            {
                jsondata.city = value.value().get<string>();
            }
            else if (value.key() == "state")
            {
                jsondata.state = value.value().get<string>();
            }
            else if (value.key() == "car")
            {
                jsondata.car = value.value().get<string>();
            }
            else if (value.key() == "car_model")
            {
                jsondata.car_model = value.value().get<string>();
            }
            else if (value.key() == "car_color")
            {
                jsondata.car_color = value.value().get<string>();
            }
            else if (value.key() == "favorite_movie")
            {
                jsondata.favorite_movie = value.value().get<string>();
            }
            else if (value.key() == "pet")
            {
                jsondata.pet = value.value().get<string>();
            }
            else if (value.key() == "job_title")
            {
                jsondata.job_title = value.value().get<string>();
            }
            else if (value.key() == "phone_number")
            {
                jsondata.phone_number = value.value().get<string>();
            }
            else if (value.key() == "latitude")
            {
                jsondata.latitude = value.value().get<double>();
            }
            else if (value.key() == "longitude")
            {
                jsondata.longitude = value.value().get<double>();
            }
            else if (value.key() == "stocks")

            {

                for (const auto &stock : value.value().items())
                {
                    stocks.push_back(stock.value());
                }
            }

            else
            {
                cout << "No key found " << endl;
            }

            //  cout << value.key() << " : " << value.value() << "\n";
        }
        gps.lat = jsondata.latitude;
        gps.lon = jsondata.longitude;
        jsondata.gps = gps;
        jsondata.stocks = stocks;
        JsonDataList.push_back(jsondata);
    }

    // To make bettter balance BST, randomly shuffle the json lines
    unsigned seed = chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
    shuffle(JsonDataList.begin(), JsonDataList.end(), default_random_engine(seed));

    // Insert data in BST and linkedList
    for (JsonData data : JsonDataList)

    {
        /**
         * The expression bstMapInt["id"].insert(id;
         * will insert a value into the BinarySearchTree associated with the key "id".
         * If "id" is not already present in the map,
         * this expression will create a new BinarySearchTree with an empty root
         * and then insert value into it.
         *  If "id" is already present in the map, this expression will insert value
         *  into the existing BinarySearchTree associated with "id".
         */
        bstMapInt["id"].insert(data.id, data);
        // BST for last_name
        bstMapString["last_name"].insert(data.last_name, data);
        // BST for email
        bstMapString["email"].insert(data.email, data);
        // BST for car_model
        bstMapString["car_model"].insert(data.car_model, data);
        // BST for job_title
        bstMapString["job_title"].insert(data.job_title, data);
        // BST for address
        bstMapString["address"].insert(data.address, data);
        // BST for phone_number
        bstMapString["phone_number"].insert(data.phone_number, data);
        // BST for latitude
        bstMapDouble["latitude"].insert(data.latitude, data);
        // BST for GPS
        bstMapGPS["GPS"].insert(data.gps, data);
        // insert JsonData in linked_list
        l.append(new JsonData(data));
    }
    // cout << "Print list " << endl;
    // l.printValue();
    // cout << endl;

    // print all trees : inorder trasversal
    // for (auto i : bstMapInt)
    // {
    //     bstMapInt[i.first].print();
    //     cout << endl;
    // }
    // for (auto i : bstMapString)

    // {   cout<< "----------- " << i.first<< " ------";
    //     bstMapString[i.first].print();
    //     cout << endl;
    // }
    // for (auto i : bstMapDouble)
    // {
    //     bstMapDouble[i.first].print();
    //     cout << endl;
    // }
    // for (auto i : bstMapGPS)
    // {
    //     bstMapGPS[i.first].print();
    //     cout << endl;
    // }

    // mapdata is used later during meneu display and it is only used for console user friendly
    map<string, string> mapdata;
    mapdata["1"] = "id";
    mapdata["2"] = "last_name";
    mapdata["3"] = "email";
    mapdata["4"] = "car_model";
    mapdata["5"] = "job_title";
    mapdata["6"] = "address";
    mapdata["7"] = "phone_number";
    mapdata["8"] = "latitude";
    mapdata["9"] = "GPS";
    string key;  // hold meneu option
    string data; // hold searching values
    /**
     * Display the meneu in console to search values in respective BST and linkedlist
     It is infine loop and only terminate if user press 10
    */
    while (true)
    {
        cout << "Choose search option (Example: enter 2 for last_name) :" << endl;
        cout << "1. id " << endl;
        cout << "2. last_name " << endl;
        cout << "3. email " << endl;
        cout << "4. car_model " << endl;
        cout << "5. job_title " << endl;
        cout << "6. address " << endl;
        cout << "7. phone_number " << endl;
        cout << "8. latitude " << endl;
        cout << "9. GPS " << endl;
        cout << "10. exit a program " << endl;
        cin >> key; // take input
        if (key == "10")
        {
            break;
        }
        // Search GPS on  respective BST and linkedList and print result
        else if (key == "9")
        {
            cout << "Enter value to latitude " << endl;
            cin >> data;
            GPS gp;
            gp.lat = stod(data);
            cout << "Enter value to longitude " << endl;
            cin >> data;
            gp.lon = stod(data);
            cout << "############# Searching Start #################" << endl;
            cout << "Searching for "
                 << "(" << gp.lat << ", " << gp.lon << ")"
                 << " in BST by " << mapdata[key] << endl;
            // Search gps in BST and display found data with number of nodes and searching time
            auto start = chrono::high_resolution_clock::now();

            bstMapGPS[mapdata[key]].printSearch(bstMapGPS[mapdata[key]].search(gp));
            printTime(start, false);
            cout << "***************************" << endl;
            cout << "Searching for "
                 << "(" << gp.lat << ", " << gp.lon << ")"
                 << " in LinkList by " << mapdata[key] << endl;
            auto start1 = chrono::high_resolution_clock::now();

            l.printSearch(l.find(gp));
            printTime(start1, true);
        }

        else
        {
            cout << "Enter value to search " << endl;
            cin.ignore();
            getline(cin, data); // take space seperated values as well from console

            cout << "############# Searching Start #################" << endl;
            cout << "Searching for \"" << data << "\"  in BST by " << mapdata[key] << endl;

            // Search item on  respective Integer BST and linkedList and print result

            if (mapdata[key] == "id")
            {
                int value = stoi(data);
                auto start = chrono::high_resolution_clock::now();
                // Search item on BST and display result
                bstMapInt[mapdata[key]].printSearch(bstMapInt[mapdata[key]].search(value));
                printTime(start, false);

                cout << "***************************" << endl;
                cout << "Searching for \"" << data << "\"  in LinkList by " << mapdata[key] << endl;
                auto start1 = chrono::high_resolution_clock::now();

                l.printSearch(l.find(data, mapdata[key]));
                printTime(start1, true);
            }
            // Search item on respective double BST and linkedList and print result

            else if (mapdata[key] == "latitude")
            {
                double doubleValue = stod(data);
                auto start = chrono::high_resolution_clock::now(); // start time for BST search
                // Search item on BST and display result
                bstMapDouble[mapdata[key]].printSearch(bstMapDouble[mapdata[key]].search(doubleValue));
                printTime(start, false);

                cout << "***************************" << endl;

                cout << "Searching for \"" << data << "\"  in LinkList by " << mapdata[key] << endl;
                auto start1 = chrono::high_resolution_clock::now(); // start time for LinkedList search
                l.printSearch(l.find(data, mapdata[key]));
                printTime(start1, true);
            }
            // Search item on respective string BST and linkedList and print result
            else
            {
                auto start = chrono::high_resolution_clock::now(); // start time for BST search
                // seacrh data in bst and print the result
                bstMapString[mapdata[key]].printSearch(bstMapString[mapdata[key]].search(data));
                // print search time
                printTime(start, false);
                cout << "***************************" << endl;
                cout << "Searching for \"" << data << "\"  in LinkList by " << mapdata[key] << endl;

                auto start1 = chrono::high_resolution_clock::now(); // start time for LinkedList search
                l.printSearch(l.find(data, mapdata[key]));
                printTime(start1, true);
            }
        }

        cout << endl;
    }

    return 0;
}
