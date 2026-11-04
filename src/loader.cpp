#include "loader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

// Given a line like "title: Binary Search Trees" and the label "title: ",
// return the part after the label. Returns "" if the label doesn't match.
static std::string getValue(const std::string& line, const std::string& label) {
    if (line.compare(0, label.size(), label) != 0) {
        return "";
    }
    return line.substr(label.size());
}

bool loadDocument(const std::string& path, Document& doc) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Could not open: " << path << "\n";
        return false;
    }

    std::string line;

    // Header: id, title, category, year (in this order)
    std::getline(file, line);
    std::string idText = getValue(line, "id: ");

    std::getline(file, line);
    std::string title = getValue(line, "title: ");

    std::getline(file, line);
    std::string category = getValue(line, "category: ");

    std::getline(file, line);
    std::string yearText = getValue(line, "year: ");

    // Reject the file if any header field is missing
    if (idText.empty() || title.empty() || category.empty() || yearText.empty()) {
        std::cout << "Bad header in: " << path << "\n";
        return false;
    }

    doc.id = std::atoi(idText.c_str());
    doc.title = title;
    doc.category = category;
    doc.year = std::atoi(yearText.c_str());

    // Skip the blank line after the header
    std::getline(file, line);

    // The rest of the file is the content
    doc.content = "";
    while (std::getline(file, line)) {
        doc.content += line + " ";
    }

    return true;
}

std::vector<Document> loadAllDocuments(const std::vector<std::string>& paths) {
    std::vector<Document> docs;
    for (size_t i = 0; i < paths.size(); i++) {
        Document d;
        if (loadDocument(paths[i], d)) {
            docs.push_back(d);
        }
    }
    return docs;
}