
## P01 - Parse JSON files , build a data structure and search the record
### Madhav Adhikari
### Description:
Using using Mockaroo, we created random_person_data.json files where Json have 16 elements. This program  have  binary search tree data  and linked list structure to load data and search the respective data and compare the time difference between them.Since Most of these data elements are easily sorted and made searchable so we can get O(logn) time complexcity to search data from BST. This program made the binary search tree/linkedlist for following values only 8 of the 16 values ( GPS will be used to search data by pairing latitude and longitude)
 - "id";
 - "last_name";
 - "email";
 - "car_model";
 - "job_title";
 - "address";
 - "phone_number
 - "latitude";
 - "GPS";

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
