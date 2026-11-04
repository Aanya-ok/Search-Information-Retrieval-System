#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include "document.h"

// Read one document from a file. Returns true if it worked.
bool loadDocument(const std::string& path, Document& doc);

// Read every listed file. Returns the documents that loaded successfully.
std::vector<Document> loadAllDocuments(const std::vector<std::string>& paths);

#endif