// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
set<string> wordleHelper(string& alphabet, string floating, string& word, set<string> psol, int n);
bool wordIsReady(string& word, string floating);
/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    // recursive backtracking type thang here so what I need to do is 
    // write a function to compute all possible words that exist given 
    // a string containing the already guessed letters that are IN THE 
    // CORRECT LOCATION

    // the FLOATING string is a string of letters that MUST appear in the 
    // word somewhere 

    // we return set of all words

    // okay so we can do like two for loops here that will backtrack
    // for the solution and reaches the length of size n ig 
    // we can get the length of the word by the length of the in 
    int n = in.length();
    // pass this off
    string word = in;
    set<string> realWords;
    set<string> psol;
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    psol = wordleHelper(alpha, floating, word, psol, n);
    // once we have the set of possible solutions we can check them with 
    // the dictionary and from there we polish and cut off and return only 
    // valid words from the recursive solution
    // set<string>::iterator jt = 
    cout << "entered the wordle" << endl;
    set<string>::iterator it = psol.begin();
    for (; it != psol.end(); ++it) {
      string currWord = *it;
      if (dict.find(currWord) != dict.end()) {
        realWords.insert(*it);
      }
    }
  return realWords;
}

// Define any helper functions here
set<string> wordleHelper(string& alphabet, string floating, string& word, set<string> psol, int n) {
    // base case here for string of length n 
    cout << "Current Word:" << word << endl;
    if (wordIsReady(word, floating)) {
      cout << word << endl;
      psol.insert(word);
    }
    // test
    // recursive case for finding solution 
    else {
        // try letters in the floating one at a time 
        for (unsigned int i = 0; i < word.size(); ++i) {
            // make sure we can make changes to correct location
            if (word[i] != '-') {
                break;
            }
            for (unsigned int j = 0; j < alphabet.size(); ++j) {
                // here is where we would insert and change the word?
                // issue here is that with the - tags in the word this 
                // means the word would trigger the base case since it 
                // matches the word here... so what to do.
                word[i] = floating[j];
                // recursive call again 
                wordleHelper(alphabet, floating, word, psol, n);
            }
        }
    }
    return psol;
}

// Helper function for determining if word is only filled with alphabet
bool wordIsReady(string& word, string floating) {
    for (unsigned int i = 0; i < word.size(); ++i) {
      // short circuit here
        if (word[i] == '-') {
            return false;
        }
        // word is ready will only get called when the word is full so
        // we can iterate and check if the word matches all the floating words
        for (unsigned int j = 0; j < floating.size(); ++j) {
          if (word[i] == floating[j]) {
            // delete the floating letters at pos j
            floating.erase(floating.begin() + j);
          }
        }
    }
    if (floating.size() == 0) {
      return true;
    }
    else {
      return false;
    }
}
