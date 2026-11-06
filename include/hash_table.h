#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>

// One entry in a bucket's linked list
struct HashNode {
    std::string key;
    int value;
    HashNode* next;
};

// Hash table with separate chaining: maps a string key to an int value
class HashTable {
public:
    HashTable(int startBuckets = 8);
    ~HashTable();

    // Stop accidental copying (copying would share our linked lists)
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(const std::string& key, int value);          // add, or update if key exists
    bool search(const std::string& key, int& value) const;   // true if found, value filled in
    bool remove(const std::string& key);                     // true if something was removed

    int size() const;            // number of stored keys
    int bucketCount() const;     // number of buckets
    double loadFactor() const;   // size / bucketCount
    long collisions() const;     // inserts that landed in a non-empty bucket
    int longestChain() const;    // length of the longest bucket list
    void print() const;          // show every bucket

private:
    std::vector<HashNode*> buckets;
    int numItems;
    long numCollisions;

    unsigned long hashFunction(const std::string& key) const;
    int indexFor(const std::string& key, int count) const;
    void resize();
};

#endif