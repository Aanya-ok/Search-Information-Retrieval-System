#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "search.h"

// Build a small hardcoded collection (we'll load from files later)
std::vector<Document> createSampleDocuments() {
    std::vector<Document> docs;

    docs.push_back({1, "Binary Search Trees", "DSA", 2021,
        "A binary search tree stores keys in sorted order. Each node has a left "
        "and right child. Search, insert and delete take O(log n) on a balanced tree."});

    docs.push_back({2, "Tree Traversal Algorithms", "DSA", 2020,
        "Tree traversal visits every node of a tree. Inorder, preorder and postorder "
        "are the common traversal methods for a binary tree."});

    docs.push_back({3, "Hash Tables and Collisions", "DSA", 2022,
        "A hash table maps keys to values using a hash function. Collisions are "
        "handled by chaining or probing."});

    docs.push_back({4, "Introduction to Relational Databases", "DBMS", 2019,
        "A relational database stores data in tables. SQL is used to query data. "
        "Indexes such as a B tree make search faster."});

    docs.push_back({5, "Object Oriented Programming in Java", "OOP", 2018,
        "Java supports inheritance, polymorphism and encapsulation. A class is a "
        "blueprint for objects."});

    docs.push_back({6, "Sorting Algorithms Overview", "DSA", 2023,
        "Merge sort and quick sort run in O(n log n) on average. Bubble sort and "
        "insertion sort are simpler but slower."});

    return docs;
}

void listAll(const std::vector<Document>& docs) {
    for (size_t i = 0; i < docs.size(); i++) {
        std::cout << docs[i].id << ". " << docs[i].title
                  << " [" << docs[i].category << ", " << docs[i].year << "]\n";
    }
}

int main() {
    std::vector<Document> docs = createSampleDocuments();
    std::string choice;

    std::cout << "=====================================\n";
    std::cout << "  MiniSearch - DSA Search Engine\n";
    std::cout << "=====================================\n";

    while (true) {
        std::cout << "\n1. List all documents\n";
        std::cout << "2. Search (linear search)\n";
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
        } else if (choice == "0") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}