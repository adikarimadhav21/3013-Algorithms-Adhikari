/*****************************************************************************
*
*  Author:           Madhav Adhikari
*  Email:            madhikari0624@my.msutexas.edu
*  Label:            P03
*  Title:            Trie tree data structure.
*  Course:           CMPS 3013
*  Semester:         Spring 2023
*
*  Description:
*        This is class that loads list of words in Trie tree data structure.
*        and allow user to search words
*
*  Usage:
*        To perform "autosuggestions" when a user types characters at the console
*        #include "tries.hpp"
*        Trie t;
*        t.insert("words");
*        t.search("word");
*  Files:
   N/A
*****************************************************************************/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// A node in the Trie tree data structure

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children; // The child nodes of this node, mapped by character
    bool is_end_of_word;                      // Indicates whether this node represents the end of a word

    TrieNode()
    {
        is_end_of_word = false;
    }
};

/**
 * Class Trie
 *
 * Description:
 *       This class implements trie tree data structure where word is insert and search accordingly
 *
 * Public Methods:
 *          Trie()
 *    void insert(string word
 *    vector<string> search(string prefix)
 *
 * Private Methods:
 *  void collectWords(TrieNode* node, string prefix, vector<string>& result
 *
 * Usage:
 *  Trie()  // create instance of Trie
 *   void insert(string word) // convert words in lower case and
 *                               add item on trie
 *  vector<string> search(string prefix)) // search any item in trie
 * void collectWords(TrieNode* node, string prefix, vector<string>& result //Recursively collect
 *                                                       all words in the subtree rooted at the last node
 */

class Trie
{
public:
    TrieNode *root; // The root node of the tree

    Trie()
    {
        root = new TrieNode();
    }

    /**
     * Public : insert
     *
     * Description:
     *  The method takes a word as input, which is the string to be inserted into the Trie tree.
     * For each character c, it checks if the current node node has a child node that represents
     *  that character. It does this by looking for c in the children map of node.
     * If there is no such child node, it creates a new TrieNode object and
     *  adds it as a child of the current node, with the character c as
     *  the key in the children map.
     *
     * Params:
     *      [string]     :  word
     *
     * Returns:
     *      void
     */

    void insert(string word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children.count(c))
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->is_end_of_word = true;
    }

    // Searches for all words in the Trie tree that match the given prefix

    vector<string> search(string prefix)
    {
        TrieNode *node = root;

        // Traverse the Trie tree to find the node that represents the last character of the prefix
       
        for (char c : prefix)
        {
            if (!node->children.count(c))
            {
                return {};
            }
            node = node->children[c];
        }
        // Initialize an empty vector to collect the matching words
        vector<string> result;
        // If the last node represents the end of a word, add the prefix itself to the result vector
       
        if (node->is_end_of_word)
        {
            result.push_back(prefix);
        }
       
        // Recursively collect all words in the subtree rooted at the last node
        dfs(node, prefix, result);
        // Return the vector of matching words
        return result;
    }

private:

   // Recursively collects all words in the subtree rooted at the given node that match the given prefix
   
void dfs(TrieNode* node, string& word, vector<string>& matched_words) {
    for (auto& child : node->children) {
        char ch = child.first;
        word += ch;
        if (child.second->is_end_of_word) {
            matched_words.push_back(word);
        }
        dfs(child.second, word, matched_words);
        word.pop_back(); // restore the word to its previous state
    }
}
};
