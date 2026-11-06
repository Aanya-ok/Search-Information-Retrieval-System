#include <iostream>
#include <cassert>
#include "tokenizer.h"

int main() {
    // Basic split and lowercase
    std::vector<std::string> t1 = tokenize("Binary-Search Trees!");
    assert(t1.size() == 3);
    assert(t1[0] == "binary");
    assert(t1[1] == "search");
    assert(t1[2] == "trees");

    // Empty string gives no tokens
    assert(tokenize("").empty());

    // Only punctuation gives no tokens
    assert(tokenize("...!!!").empty());

    // Text ending mid-word still returns the last word
    std::vector<std::string> t2 = tokenize("hello world");
    assert(t2.size() == 2);
    assert(t2[1] == "world");

    // Digits are kept
    std::vector<std::string> t3 = tokenize("O(n2) sort");
    assert(t3.size() == 3);   // o, n2, sort

    // Stopwords
    assert(isStopWord("the"));
    assert(!isStopWord("tree"));

    std::vector<std::string> t4 = removeStopWords(tokenize("The tree is big"));
    assert(t4.size() == 2);   // tree, big

    std::cout << "All tokenizer tests passed.\n";
    return 0;
}