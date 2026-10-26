#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

// One searchable document in our collection
struct Document {
    int id;
    std::string title;
    std::string category;
    int year;
    std::string content;
};

#endif