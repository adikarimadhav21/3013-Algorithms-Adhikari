
## P02 - AutoComplete in Linear Time
### Madhav Adhikari
### Description:
loading a singly linked list with dictionary words, then timing how it takes to look them up. I have applied the following approaches to this program.

- Read text file and load in linkedList by lowering each words
- Display required time to load
- Ask user to search words and capture of keyboard input, without hitting the enter key (using mygetch.hpp)            
- Search the required letter in LinkedList and provide 10 autosuggestion words with search time and number of matched words
- Append the letter with another typed letter and search in linkedList
- Continue the program till typed capital 'Z'


### Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | main.cpp       | driver program   |
|   2   | singleList.hpp  | header file to load/search words in linkedList   |
|3|timer.hpp| header file to calculate execution time|
|4|mygetch.hpp| header files to capture of keyboard input, without hitting the enter key|
|5|termcolor.hpp| header file to color text|
|6|dictionary.txt| input data which have list of words|
|7|output_file.pdf| screenshot of output|
|8|banner.txt|Banner for P02|

### Instructions

- Make sure you placed text files and headers files in the same location of driver class
- Run the program and type the word to search via  console 

### Example Command:
- None for now
