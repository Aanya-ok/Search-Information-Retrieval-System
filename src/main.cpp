#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "search.h"
#include "loader.h"
#include "tokenizer.h"
#include "hash_table.h"

void listAll(const std::vector<Document>& docs) {
    for (size_t i = 0; i < docs.size(); i++) {
        std::cout << docs[i].id << ". " << docs[i].title
                  << " [" << docs[i].category << ", " << docs[i].year << "]\n";
    }
}

void showTokens(const std::string& text) {
    std::vector<std::string> tokens = tokenize(text);
    std::cout << "All tokens       : ";
    for (size_t i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i] << " | ";
    }

    std::vector<std::string> filtered = removeStopWords(tokens);
    std::cout << "\nWithout stopwords: ";
    for (size_t i = 0; i < filtered.size(); i++) {
        std::cout << filtered[i] << " | ";
    }
    std::cout << "\n";
}

// Count how many times each word appears, using our own hash table
void hashTableDemo() {
    std::string text;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, text);

    HashTable table(4);
    std::vector<std::string> words = removeStopWords(tokenize(text));

    for (size_t i = 0; i < words.size(); i++) {
        int count = 0;
        if (table.search(words[i], count)) {
            table.insert(words[i], count + 1);
        } else {
            table.insert(words[i], 1);
        }
    }

    table.print();
    std::cout << "\nWords stored  : " << table.size() << "\n";
    std::cout << "Buckets       : " << table.bucketCount() << "\n";
    std::cout << "Load factor   : " << table.loadFactor() << "\n";
    std::cout << "Collisions    : " << table.collisions() << "\n";
    std::cout << "Longest chain : " << table.longestChain() << "\n";
}

int main() {
    std::vector<std::string> files;
    files.push_back("data/sample_documents/doc1.txt");
    files.push_back("data/sample_documents/doc2.txt");
    files.push_back("data/sample_documents/doc3.txt");
    files.push_back("data/sample_documents/doc4.txt");
    files.push_back("data/sample_documents/doc5.txt");
    files.push_back("data/sample_documents/doc6.txt");

    std::vector<Document> docs = loadAllDocuments(files);
    std::cout << "Loaded " << docs.size() << " documents.\n";

    std::string choice;

    std::cout << "=====================================\n";
    std::cout << "  MiniSearch - DSA Search Engine\n";
    std::cout << "=====================================\n";

    while (true) {
        std::cout << "\n1. List all documents\n";
        std::cout << "2. Search (linear search)\n";
        std::cout << "3. Show tokens of a text (tokenizer demo)\n";
        std::cout << "4. Word counter (hash table demo)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            listAll(docs);
        } else if (choice == "2") {
            std::string keyword;
            std::cout << "Enter keyword: ";
            std::getline(std::cin, keyword);
            std::cout << "\n";
            linearSearch(docs, keyword);
        } else if (choice == "3") {
            std::string text;
            std::cout << "Enter text: ";
            std::getline(std::cin, text);
            showTokens(text);
        } else if (choice == "4") {
            hashTableDemo();
        } else if (choice == "0") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}