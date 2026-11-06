#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "search.h"
#include "loader.h"
#include "tokenizer.h"

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
        } else if (choice == "0") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}