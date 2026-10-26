#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "document.h"

std::string toLowerCase(const std::string& text);
int countOccurrences(const std::string& text, const std::string& word);
void linearSearch(const std::vector<Document>& docs, const std::string& keyword);

#endif