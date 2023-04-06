/*****************************************************************************
*
*  Author:           Madhav Adhikari
*  Email:            madhikari0624@my.msutexas.edu
*  Label:            P03
*  Title:            Processing in Trie Tree Time
*  Course:           CMPS 3013
*  Semester:         Spring 2023
*
*  Description:
*        This is program that reads the words from dictionary json file,
         loads list of words in Trie tree and calculate loading time,
*        and allow user to search words via console and provide autosuggestion
to user
*  Usage:
*        To perform "autosuggestions" when a user types characters at the
console
*
*  Files:
   main.cpp    : driver program
   tries.hpp : header file to load/search words in Trie Tree
   json.hpp:  header files to read Json file (nlohmann)
   timer.hpp:  header file to calculate execution time
   mygetch.hpp: header files to capture of keyboard input, without hitting the
                enter key and optionally not even reflecting on the console that anything
                happened.
   termcolor.hpp: header file to color text
   banner.txt  : own banner for this program
   dist.json : input data which have list of words
   output_file : screenshot of output
*****************************************************************************/
#include "json.hpp"
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include "tries.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace nlohmann;

int main()
{
  char k;           // holder for character being typed
  string word = ""; // variable to concatenate letters to search
  Trie trie;
  Timer T; // create a timer

  cout << "Words load in Tries started " << endl;
  T.Start();

  // Read Json file

  ifstream inputfile("dist.json");
  if (!inputfile.is_open())
  {
    cout << "Error to open files" << endl;
  }

  json jsonData = json::parse(inputfile);

  for (auto item : jsonData.items())
  {
    trie.insert(item.key()); // insert word into Trie
  }
  T.End(); // load end time

  // Calculate loading time

  cout << "words load completed in  "
       << printf("%.17f", (double)T.NanoSeconds() / 1000000000) << " seconds"
       << endl;

  vector<string> matches; // holder for words being matched

  // While capital Z is not typed keep looping

  while ((k = getch()) != 'Z')
  {
    T.Start(); // search start time

    // If backspace is pressed, deletes last letter from "word".

    if ((int)k == 127)
    {
      if (word.size() > 0)
      {
        word = word.substr(0, word.size() - 1);
      }
    }
    else
    {

      // Make sure  only apha letter is allowed
      if (!isalpha(k))
      {
        cout << "Letters only!" << endl;
        continue;
      }

      // Make letter to lowercase. Since any letter with ascii value < 97 is
      // capital so we lower it

      if ((int)k < 97)
      {
        k += 32;
      }
      word += k; // append char to word to search the prefix in words
    }

    // Search prefix in words and get autosuggestion words

    matches = trie.search(word);

    T.End(); // search end time

    // print current substring in console as red color text
    cout << "User input: " << termcolor::red << word << " " << termcolor::reset
         << endl;

    // print number of autosuggestions words and searched time

    cout << matches.size() << " words found in "
         << printf("%.17f", (double)T.NanoSeconds() / 1000000000) << " seconds"
         << endl;

    // Display only 10 autosuggestion words in green color

    cout << termcolor::green;
    int count = 0;
    for (string word : matches)
    {
      if (count >= 10)
      {
        break;
      }
      cout << word << " ";
      count++;
    }
    cout << termcolor::reset << endl
         << endl;
  }
}