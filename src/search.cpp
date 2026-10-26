#include "search.h"
#include <iostream>

// Convert text to lowercase so "Tree" and "tree" match
std::string toLowerCase(const std::string& text) {
    std::string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

// Count how many times 'word' appears in 'text'
int countOccurrences(const std::string& text, const std::string& word) {
    if (word.empty()) return 0;

    int count = 0;
    size_t pos = text.find(word, 0);
    while (pos != std::string::npos) {
        count++;
        pos = text.find(word, pos + word.size());
    }
    return count;
}

// Linear search: check EVERY document one by one
void linearSearch(const std::vector<Document>& docs, const std::string& keyword) {
    std::string key = toLowerCase(keyword);
    int found = 0;

    for (size_t i = 0; i < docs.size(); i++) {
        std::string text = toLowerCase(docs[i].title + " " + docs[i].content);
        int matches = countOccurrences(text, key);

        if (matches > 0) {
            found++;
            std::cout << found << ". " << docs[i].title << "\n";
            std::cout << "   Category: " << docs[i].category
                      << " | Year: " << docs[i].year
                      << " | Matches: " << matches << "\n";
        }
    }

    std::cout << "\nScanned " << docs.size() << " documents, "
              << found << " matched.\n";
}