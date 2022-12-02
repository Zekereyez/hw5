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
void findWords(const string& alphabet, string& word, const set<string>& dict, string floating, set<string>& psol, int pos, unsigned int dashes);
void tryLetter(const string& alphabet, string& word, const set<string>& dict, string floating, set<string>& psol, int pos, unsigned int dashes);
bool wordExist(const string& word, const set<string>& dict);
void checkFloating(string& floating, string& word);
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
  set<string> soln;
  string alpha = "abcdefghijklmnopqrstuvwxyz";
  int pos = 0;
  unsigned int dashes = 0;
  for (auto letter : in) {
    if (letter == '-') {
      dashes++;
    }
  }
  if (dashes == floating.size()) {
    findWords(floating, word, dict, floating, soln, pos, dashes);
  }
  else {
    findWords(alpha, word, dict, floating, soln, pos, dashes);
  }
  return soln;
}

// Define any helper functions here

// Helper function for determining if word is only filled with alphabet
void findWords(const string& alphabet, string& word, const set<string>& dict, string floating, set<string>& psol, int pos, unsigned int dashes) {
  // base case 
  string ff = floating;
  if (pos == word.size()) {
    // we have now a complete word that needs to be checked if it 
    // has the floating letters in it 
    if (wordExist(word, dict)) {
      checkFloating(ff, word);
      // at the end of looping here we need to check and see if the floating string
      // is empty, if so then word is valid
      if (ff.size() == 0) {
        psol.insert(word);
      }
    }
    return;
  }
  // we try a letter if we are at a "-" pos in the letter
  if (word[pos] == '-') {
    // check word and update the current floating string 
    checkFloating(ff, word);
    if (ff.size() == 0) {
      // this means we fill the word with the alphabet 
      tryLetter(alphabet, word, dict, ff, psol, pos, dashes);
    }
    if (dashes == ff.size()) {
      // we should try the letters of the floating first
      tryLetter(floating, word, dict, ff, psol, pos, dashes);
    }
    else {
      // normal case: try alphabet letters for the word
      tryLetter(alphabet, word, dict, floating, psol, pos, dashes);
    }
  }
  else {
    pos++;
    findWords(alphabet, word, dict, floating, psol, pos, dashes);
  }
}

void tryLetter (const string& alphabet, string& word, const set<string>& dict, string floating, set<string>& psol, int pos, unsigned int dashes) {
  // this is where the recursive magic is going to happen. 
  // we should only enter this function if we know we can try 
  // a word. I'm tired of this whole checking bullshit atp 

  for (unsigned int i = 0; i < alphabet.size(); ++i) {
    // so what i do here is just try a letter at the current location and 
    // recursively call the findWords function with the updated pos
    word[pos] = alphabet[i];
    dashes--;
    pos++;
    findWords(alphabet, word, dict, floating, psol, pos, dashes);
    pos--;
    dashes++;
  }
  // if no found then go back to what pos and space was before
  word[pos] = '-';
}

bool wordExist(const string& word, const set<string>& dict) {
  if (dict.find(word) != dict.end()) {
    return true;
  }
  return false;
}

void checkFloating(string& floating, string& word) {
  for (auto letter : word) {
    size_t index = floating.find(letter);
    if (index !=std::string::npos) {
      floating.erase(floating.begin()+index);
    }
  }
}