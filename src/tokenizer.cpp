#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> words;
    std::string current = "";

    for (size_t i = 0; i < text.size(); i++) {
        unsigned char c = text[i];

        if (std::isalnum(c)) {
            // Part of a word: add it in lowercase
            current += static_cast<char>(std::tolower(c));
        } else {
            // Separator: if we were building a word, finish it
            if (!current.empty()) {
                words.push_back(current);
                current = "";
            }
        }
    }

    // The text may end in the middle of a word
    if (!current.empty()) {
        words.push_back(current);
    }

    return words;
}

bool isStopWord(const std::string& word) {
    static const char* stopWords[] = {
        "a", "an", "the", "is", "are", "of", "and", "or", "to",
        "in", "on", "for", "with", "by", "as", "at", "it", "this", "that"
    };
    const int count = sizeof(stopWords) / sizeof(stopWords[0]);

    for (int i = 0; i < count; i++) {
        if (word == stopWords[i]) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> removeStopWords(const std::vector<std::string>& words) {
    std::vector<std::string> result;
    for (size_t i = 0; i < words.size(); i++) {
        if (!isStopWord(words[i])) {
            result.push_back(words[i]);
        }
    }
    return result;
}