/*****************************************************************************
*
*  Author:           Madhav Adhikari
*  Email:            madhikari0624@my.msutexas.edu
*  Label:            P02
*  Title:            SingleLinkedList
*  Course:           CMPS 3013
*  Semester:         Spring 2023
*
*  Description:
*        This is class that loads list of words in single linked list
*        and allow user to search words
*
*  Usage:
*        To perform "autosuggestions" when a user types characters at the console
*        #include "singleList.hpp"
*        LinkedList L;
*        l.append("words");
*        l.findwords("word");
*  Files:
   N/A
*****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a wordNode  struct to hold a word

struct wordNode
{
    string word;
    wordNode *next;
    wordNode(string value)
    {
        word = value;
        next = nullptr;
    }
};

/**
 * Class LinkedList
 *
 * Description:
 *       This class implements linkedList data structure where word is insert and search accordingly
 *
 * Public Methods:
 *          LinkedList()
 *    void tailInsert(wordNode *new_node)
 *    void append(string value)
 *    vector<string> findWords(string target)
 *    void printValue()
 *
 * Private Methods:
 *  N/A
 *
 * Usage:
 *  LinkedList()  // create instance of LinkedList
 *  void tailInsert(wordNode *new_node)    // add item on tail
 *  void append(string value)  // convert words in lower case and call tailInsert
 *                              method to add item on tail
 *  vector<string> findWords(string target) // search any item in linkedlist
 *  void printValue()  // trasversal linkedList
 */

class LinkedList
{
    wordNode *head;
    wordNode *tail;

public:
    LinkedList()
    {
        head = tail = nullptr;
    }

    /**
     * Public : tailInsert
     *
     * Description:
     *     Add word in linkedList at the end of list
     *
     * Params:
     *      [wordNode]     :  *new_node
     *
     * Returns:
     *      void
     */

    void tailInsert(wordNode *new_node)
    {
        tail->next = new_node;
        tail = new_node;
    }

    /**
     * Public : append
     *
     * Description:
     *     Convert word to lower case and  add word in linkedList at the end of list
     *
     * Params:
     *      [string]     :  value
     *
     * Returns:
     *      void
     */

    void append(string value)
    {
        transform(value.begin(), value.end(), value.begin(), ::tolower);

        wordNode *temp = new wordNode(value);
        if (tail == nullptr)
        {
            head = tail = temp;
        }
        else
        {
            tailInsert(temp);
        }
    }

    // print all linkedList values

    void printValue()
    {
        wordNode *travell = head;
        cout << "List of words==> ";

        while (travell != NULL)
        {
            cout << travell->word << " ";
            travell = travell->next;
        }
        cout << endl;
    }

    /**
     * Public : findWords
     *
     * Description:
     *     find the subtstring/words in the linked list and return a vector of all matching words
     *
     * Params:
     *      [string]     :  target
     *
     * Returns:
     *      vector<string>
     */

    vector<string> findWords(string target)
    {
        vector<string> result;
        wordNode *current = head;
        while (current != nullptr)
        {

            if (current->word.substr(0, target.size()) == target)
            {
                result.push_back(current->word);
            }
            current = current->next;
        }
        return result;
    }
};
