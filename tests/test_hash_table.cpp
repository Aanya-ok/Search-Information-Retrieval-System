#include <iostream>
#include <cassert>
#include <string>
#include "hash_table.h"

int main() {
    HashTable table(4);
    int value = 0;

    // Insert and search
    table.insert("tree", 1);
    table.insert("sort", 2);
    assert(table.size() == 2);
    assert(table.search("tree", value) && value == 1);
    assert(table.search("sort", value) && value == 2);

    // Missing key
    assert(!table.search("graph", value));

    // Updating an existing key must not add a new entry
    table.insert("tree", 99);
    assert(table.size() == 2);
    assert(table.search("tree", value) && value == 99);

    // Remove
    assert(table.remove("sort"));
    assert(table.size() == 1);
    assert(!table.search("sort", value));
    assert(!table.remove("sort"));       // already gone

    // Resize: many keys must all survive
    HashTable big(2);
    for (int i = 0; i < 1000; i++) {
        big.insert("word" + std::to_string(i), i);
    }
    assert(big.size() == 1000);
    assert(big.bucketCount() > 2);
    assert(big.loadFactor() <= 0.75);

    for (int i = 0; i < 1000; i++) {
        assert(big.search("word" + std::to_string(i), value));
        assert(value == i);
    }

    // With 1000 keys there must have been collisions
    assert(big.collisions() > 0);

    std::cout << "All hash table tests passed.\n";
    std::cout << "Buckets: " << big.bucketCount()
              << ", collisions: " << big.collisions()
              << ", longest chain: " << big.longestChain() << "\n";
    return 0;
}