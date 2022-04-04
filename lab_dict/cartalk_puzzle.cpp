/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    string line;
    ifstream file(word_list_fname);
    if(file.is_open()) {
      while (getline(file, line)) {
        if (line.size() == 5) {
          string word1 = line.substr(1, line.size() - 1);
          string word2 = line.substr(0, 1) + line.substr(2, line.size() - 1);

          if (d.homophones(line, word1) && d.homophones(line, word2)) {
            ret.push_back(std::make_tuple(line, word1, word2));
          }
        }
      }


    }
    return ret;
}
