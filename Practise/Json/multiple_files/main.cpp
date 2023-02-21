

#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <typeinfo>
#include "bst.h"

using namespace std;
using namespace nlohmann;
#include <map>

int main()
{

    // maps to store the multiples binary search tree where key is string and values is instance of BinarySearchTree
    map<string, BinarySearchTree<int>> bstMapInt;
    map<string, BinarySearchTree<string>> bstMapString;
    map<string, BinarySearchTree<double>> bstMapDouble;
    map<string, BinarySearchTree<GPS>> bstMapGPS;
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

    // read josn files .
    // todo  read multiples files
    ifstream inputfile("data/random_person_data_1.json");
    if (!inputfile.is_open())
    {
        cout << "Error to open files" << endl;
    }

    json jsonData = json::parse(inputfile);

    // loop to extract each line of json in files (like NDJson where JSON lines separted by new line charcter)
    for (auto item : jsonData.items())
    {
        cout << item.key() << " :: " << item.value() << "\n";
        int id;
        string first_name, last_name, email, address, city, state, car,
            car_model, car_color, favorite_movie, pet, job_title, phone_number;
        double latitude, longitude;
        vector<string> stocks;
        GPS gps;
        // iterate for each elements of JSON object
        for (const auto &value : item.value().items())
        {

            if (value.key() == "id")
            {
                id = value.value().get<int>();
            }

            else if (value.key() == "first_name")
            {
                first_name = value.value().get<string>();
            }
            else if (value.key() == "last_name")
            {
                last_name = value.value().get<string>();
            }
            else if (value.key() == "email")
            {
                email = value.value().get<string>();
            }
            else if (value.key() == "address")
            {
                address = value.value().get<string>();
            }
            else if (value.key() == "city")
            {
                city = value.value().get<string>();
            }
            else if (value.key() == "state")
            {
                state = value.value().get<string>();
            }
            else if (value.key() == "car")
            {
                car = value.value().get<string>();
            }
            else if (value.key() == "car_model")
            {
                car_model = value.value().get<string>();
            }
            else if (value.key() == "car_color")
            {
                car_color = value.value().get<string>();
            }
            else if (value.key() == "favorite_movie")
            {
                favorite_movie = value.value().get<string>();
            }
            else if (value.key() == "pet")
            {
                pet = value.value().get<string>();
            }
            else if (value.key() == "job_title")
            {
                job_title = value.value().get<string>();
            }
            else if (value.key() == "phone_number")
            {
                phone_number = value.value().get<string>();
            }
            else if (value.key() == "latitude")
            {
                latitude = value.value().get<double>();
            }
            else if (value.key() == "longitude")
            {
                longitude = value.value().get<double>();
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

            cout << value.key() << " : " << value.value() << "\n";
        }
        gps.lat = latitude;
        gps.lon = longitude;
        /**
         * The expression bstMapInt["id"].insert(id;
         * will insert a value into the BinarySearchTree associated with the key "id".
         * If "id" is not already present in the map,
         * this expression will create a new BinarySearchTree with an empty root
         * and then insert value into it.
         *  If "id" is already present in the map, this expression will insert value
         *  into the existing BinarySearchTree associated with "id".
         */

        bstMapInt["id"].insert(id, id, first_name, last_name, email, address, city, state, car,
                               car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);

        // todo reduce multiple lines to single line code
        //     for ( auto field:mapdata){
        //      cout<<" hi "<<field.second;
        //              bstMapString[field.second].insert(field.second, id, first_name, last_name, email, address, city, state, car,
        //                                        car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude,stocks);

        //    }
        // BST for last_name
        bstMapString["last_name"].insert(last_name, id, first_name, last_name, email, address, city, state, car,
                                         car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for Email
        bstMapString["email"].insert(email, id, first_name, last_name, email, address, city, state, car,
                                     car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for car_model
        bstMapString["car_model"].insert(car_model, id, first_name, last_name, email, address, city, state, car,
                                         car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for job_titile
        bstMapString["job_title"].insert(job_title, id, first_name, last_name, email, address, city, state, car,
                                         car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for address
        bstMapString["address"].insert(address, id, first_name, last_name, email, address, city, state, car,
                                       car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for phone_number
        bstMapString["phone_number"].insert(phone_number, id, first_name, last_name, email, address, city, state, car,
                                            car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for latitude
        bstMapDouble["latitude"].insert(latitude, id, first_name, last_name, email, address, city, state, car,
                                        car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
        // BST for GPS ( that is pair of latitude and longitude)
        bstMapGPS["GPS"].insert(gps, id, first_name, last_name, email, address, city, state, car,
                                car_model, car_color, favorite_movie, pet, job_title, phone_number, latitude, longitude, stocks);
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

    string key;
    string data;
    // Display the meneu in console to search  values in respective BST
    while (true)
    {
        cout << "Choose search option (Example enter 2 for last_name) :" << endl;
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

            // print found data after searcing data in respective BST
            bstMapGPS[mapdata[key]].printSearch(bstMapGPS[mapdata[key]].search(gp));
        }

        else
        {
            cout << "Enter value to search " << endl;
            cin >> data;
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
