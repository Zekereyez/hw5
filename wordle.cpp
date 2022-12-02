// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
set<string> wordleHelper(string& alphabet, string floating, string& word, set<string> psol, int n);
bool wordIsReady(string& word, string floating);
void findWords(string alphabet, string& word, string floating, set<string>& psol, int pos);
void tryLetter(string alphabet, string& word, string floating, set<string>& psol, int pos);
void insertWordsWithFloating(set<string>& psol, string floating, set<string>& realWords);
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
    // pass this off
    string word = in;
    set<string> realWords;
    set<string> psol;
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    // cout << "entering find words" << endl;
    unsigned int dashes = 0;
    for (auto letter : in) {
      if (letter == '-') {
        dashes++;
      }
    }
    if (dashes == floating.size()) {
      findWords(floating, word, floating, psol, pos);
    }
    else findWords(alpha, word, floating, psol, pos);
    // cout << "entered the wordle" << endl;
    // insertWordsWithFloating(psol, floating, realWords);
    // cout << "back in wordle" << endl;
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

// Helper function for determining if word is only filled with alphabet
void findWords(string alphabet, string& word, string floating, set<string>& psol, int pos) {
  // base case 
  // cout << "in find words" <<endl;
  // cout << "Word: " << word << endl;
  if (pos == word.size()) {
    // we have now a complete word that needs to be checked if it 
    // has the floating letters in it 
    for (auto letter : word) {
      for (unsigned int i = 0; i < floating.size(); ++i) {
        if (letter == floating[i]) {
          // we delete the letter from floating 
          floating.erase(floating.begin() + i);
        }
      }
    }
    // // at the end of looping here we need to check and see if the floating string
    // // is empty, if so then word is valid
    if (floating == "") {
      psol.insert(word);
    }
    return;
  }
  // we try a letter if we are at a "-" pos in the letter
  if (word[pos] == '-') {
    // cout << "entered if for tryLetter" << endl;
    tryLetter(alphabet, word, floating, psol, pos);
  }
  else {
    pos++;
    findWords(alphabet, word, floating, psol, pos);
  }
}

void tryLetter (string alphabet, string& word, string floating, set<string>& psol, int pos) {
  // this is where the recursive magic is going to happen. 
  // we should only enter this function if we know we can try 
  // a word. I'm tired of this whole checking bullshit atp 

  for (unsigned int i = 0; i < alphabet.size(); ++i) {
    // so what i do here is just try a letter at the current location and 
    // recursively call the findWords function with the updated pos
    word[pos] = alphabet[i];
    pos++;
    findWords(alphabet, word, floating, psol, pos);
    pos--;
  }
  // if no found then go back to what pos and space was before
  word[pos] = '-';
}