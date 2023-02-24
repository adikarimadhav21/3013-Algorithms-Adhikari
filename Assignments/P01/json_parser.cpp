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

// Operator overloading for case-insensitive string comparison
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
        return std::lexicographical_compare(
            str.begin(), str.end(),
            other.str.begin(), other.str.end(),
            [](char a, char b)
            {
                return std::tolower(a) < std::tolower(b);
            });
    }
};

/**
 * define the GPS struct with the operator== and operator< functions
 * operator function can used later in insert and search function to compare GPS  types data
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

// this class hold the json elements values
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

//  BinarySearchTree class is defined using a template parameter typename T,
// which allows it to work with any data type
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

    Node *search(Node *node, const T &value) const
    {
        // count number of nodes while searching the values
        static int count = 0;
        // todo while loop issue  : retain previos value
        count++;
        // calculate excuetion time to find the values in BST
        const clock_t start = clock();

        if (node == nullptr)
        {
            cout << "Comapared  to " << count << " nodes" << endl;

            clock_t end = clock();
            double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            cout << "No Record Found in " << elapsed << " seconds" << endl;

            return node;
        }
        // C++ compilier will dynamically switch < operator as per data types
        //  todo ignore case sensitive during string compare and  wildcard as well
        if (node->value == value)
        {
            if constexpr (is_same_v<T, GPS>)
            {
                cout << "Comapared "
                     << "(" << value.lat << ", " << value.lon << ") "
                     << " to" << count << " nodes" << endl;
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

            clock_t end = clock();
            double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            cout << "Found in " << elapsed << " seconds" << endl;

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
    // print the found json  if search values is found
    void printSearch(Node *result)

    {
        if (result == nullptr)
        {
            cout << "No record found" << endl;
            cout << "############ Searching end ##################" << endl;
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
            cout << "############ Searching end ##################" << endl;
        }
    }
};

int main()
{

    // maps to store the multiples binary search tree where key is string and values is instance of BinarySearchTree
    map<string, BinarySearchTree<int>> bstMapInt;
    map<string, BinarySearchTree<WildCardString>> bstMapString;
    map<string, BinarySearchTree<double>> bstMapDouble;
    map<string, BinarySearchTree<GPS>> bstMapGPS;

    // read josn files .
    // todo  read multiples files
    ifstream inputfile("data/random_person_data_1.json");
    if (!inputfile.is_open())
    {
        cout << "Error to open files" << endl;
    }

    json jsonData = json::parse(inputfile);
    double latitude, longitude;
    vector<string> stocks;
    GPS gps;
    // collect data from files
    JsonData jsondata;
    vector<JsonData> JsonDataList;
    // loop to extract each line of json in files (like NDJson where JSON lines separted by new line character)
    for (auto item : jsonData.items())
    {
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

    // to make bettter balance BST, randomly shuffle the json lines
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
    shuffle(JsonDataList.begin(), JsonDataList.end(), std::default_random_engine(seed));

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
    }
    // print all trees : inorder trasversal
    for (auto i : bstMapInt)
    {
        bstMapInt[i.first].print();
        cout << endl;
    }
    for (auto i : bstMapString)
    {
        bstMapString[i.first].print();
        cout << endl;
    }
    for (auto i : bstMapDouble)
    {
        bstMapDouble[i.first].print();
        cout << endl;
    }
    for (auto i : bstMapGPS)
    {
        bstMapGPS[i.first].print();
        cout << endl;
    }
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
    string key;
    string data;
    // Display the meneu in console to search  values in respective BST
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
        cin >> key;
        if (key == "10")
        {
            break;
        }
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
            // print found data after searcing data in respective BST
            bstMapGPS[mapdata[key]].printSearch(bstMapGPS[mapdata[key]].search(gp));
        }

        else
        {
            cout << "Enter value to search " << endl;
            cin >> data;
            cout << "############# Searching Start #################" << endl;
            cout << "Searching for \"" << data << "\"  in BST by " << mapdata[key] << endl;

            if (mapdata[key] == "id")
            {
                int value = stoi(data);
                bstMapInt[mapdata[key]].printSearch(bstMapInt[mapdata[key]].search(value));
            }
            else if (mapdata[key] == "latitude")
            {
                double doubleValue = stod(data);
                bstMapDouble[mapdata[key]].printSearch(bstMapDouble[mapdata[key]].search(doubleValue));
            }

            else
            {
                bstMapString[mapdata[key]].printSearch(bstMapString[mapdata[key]].search(data));
            }
        }

        cout << endl;
    }

    return 0;
}
