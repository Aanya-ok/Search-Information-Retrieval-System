#include "hash_table.h"
#include <iostream>

HashTable::HashTable(int startBuckets) {
    if (startBuckets < 1) {
        startBuckets = 8;
    }
    buckets.assign(startBuckets, nullptr);
    numItems = 0;
    numCollisions = 0;
}

// Free every node in every chain
HashTable::~HashTable() {
    for (size_t i = 0; i < buckets.size(); i++) {
        HashNode* node = buckets[i];
        while (node != nullptr) {
            HashNode* next = node->next;
            delete node;
            node = next;
        }
    }
}

// Polynomial hash: h = h * 31 + character, for every character
unsigned long HashTable::hashFunction(const std::string& key) const {
    unsigned long h = 0;
    for (size_t i = 0; i < key.size(); i++) {
        h = h * 31 + static_cast<unsigned char>(key[i]);
    }
    return h;
}

// Turn the hash into a valid bucket index
int HashTable::indexFor(const std::string& key, int count) const {
    return static_cast<int>(hashFunction(key) % static_cast<unsigned long>(count));
}

void HashTable::insert(const std::string& key, int value) {
    int index = indexFor(key, static_cast<int>(buckets.size()));

    // If the key already exists in this chain, update it
    HashNode* node = buckets[index];
    while (node != nullptr) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    // A new key landing in a bucket that already has something = collision
    if (buckets[index] != nullptr) {
        numCollisions++;
    }

    // Add the new node at the FRONT of the chain (O(1))
    HashNode* newNode = new HashNode;
    newNode->key = key;
    newNode->value = value;
    newNode->next = buckets[index];
    buckets[index] = newNode;
    numItems++;

    if (loadFactor() > 0.75) {
        resize();
    }
}

bool HashTable::search(const std::string& key, int& value) const {
    int index = indexFor(key, static_cast<int>(buckets.size()));

    HashNode* node = buckets[index];
    while (node != nullptr) {
        if (node->key == key) {
            value = node->value;
            return true;
        }
        node = node->next;
    }
    return false;
}

bool HashTable::remove(const std::string& key) {
    int index = indexFor(key, static_cast<int>(buckets.size()));

    HashNode* node = buckets[index];
    HashNode* prev = nullptr;

    while (node != nullptr) {
        if (node->key == key) {
            if (prev == nullptr) {
                buckets[index] = node->next;   // removing the first node
            } else {
                prev->next = node->next;       // skip over the node
            }
            delete node;
            numItems--;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

// Double the buckets and move every node to its new bucket
void HashTable::resize() {
    int newCount = static_cast<int>(buckets.size()) * 2;
    std::vector<HashNode*> newBuckets(newCount, nullptr);

    for (size_t i = 0; i < buckets.size(); i++) {
        HashNode* node = buckets[i];
        while (node != nullptr) {
            HashNode* next = node->next;                  // remember before relinking
            int index = indexFor(node->key, newCount);    // index uses the NEW size
            node->next = newBuckets[index];
            newBuckets[index] = node;
            node = next;
        }
    }
    buckets = newBuckets;
}

int HashTable::size() const {
    return numItems;
}

int HashTable::bucketCount() const {
    return static_cast<int>(buckets.size());
}

double HashTable::loadFactor() const {
    return static_cast<double>(numItems) / static_cast<double>(buckets.size());
}

long HashTable::collisions() const {
    return numCollisions;
}

int HashTable::longestChain() const {
    int longest = 0;
    for (size_t i = 0; i < buckets.size(); i++) {
        int length = 0;
        HashNode* node = buckets[i];
        while (node != nullptr) {
            length++;
            node = node->next;
        }
        if (length > longest) {
            longest = length;
        }
    }
    return longest;
}

void HashTable::print() const {
    for (size_t i = 0; i < buckets.size(); i++) {
        std::cout << "[" << i << "]: ";
        HashNode* node = buckets[i];
        while (node != nullptr) {
            std::cout << node->key << "(" << node->value << ") -> ";
            node = node->next;
        }
        std::cout << "end\n";
    }
}