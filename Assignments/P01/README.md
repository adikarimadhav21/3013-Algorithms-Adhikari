
## P01 - Parse JSON files , build a data structure and search the record
### Madhav Adhikari
### Description:
Using Mockaroo, we created random_person_data.json files where Json has 16 elements. This program has binary search tree  and a linked list data structure to load data and search the respective data by comparing the time difference between them. This program made the binary search tree/LinkedList for 8 values only ("id";"last_name"; - "email"; - "car_model"; - "job_title"; - "address";- "phone_number - "latitude"; - "GPS";) of the 16 values ( GPS will be used to search data by pairing latitude and longitude).  I have applied the following approaches to this program.

- Read JSON files and collect all data JsonData in vector JsonDataList
- To  make a better balance BST, randomly shuffle the JsonData 
- Make different BST and store them in the map ( key= element_name, value_BST), here to store different types of BST like string, double, int, GPS , template <typename T> concept is used 
- To compare the values to respective types like sting comparison with ignoring case and special character, used operator overloading concepts
- Insert all JsonData into linkedList- Ask the user to enter search parameters like 1 for id and 2 for last_name and respective intentioned search values 
- Search the required values in respective BST and LinkedList
- Count the number of nodes and calculate execution time till the required values found
- Display the result in the console 

Since most of these data elements are easily sorted and made searchable so we can get O(logn) time complexity to search data from BST. 

### Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | json.hpp        | header files of nlohmann to read the json files   |
|   2   | json_parser.cpp  | main files which have json files parser, build BST and search the data in BST      |

### Instructions

- Make sure you placed the json files inside the data folder:
- Make sure the json.hpp files download from nlohman libary and placed same location as main pasrer code (json_parser.cpp):
- Run the program and select option to seacrh and type search valves via  console 

### Example Command:
- None for now
