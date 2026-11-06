#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

// Split text into lowercase words (letters and digits only).
std::vector<std::string> tokenize(const std::string& text);

// Return true if the word is a common word we ignore (e.g. "the", "is").
bool isStopWord(const std::string& word);

// Return a copy of 'words' with stopwords removed.
std::vector<std::string> removeStopWords(const std::vector<std::string>& words);

#endif