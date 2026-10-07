#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <string>
#include <vector>

class Library {
public:
    Library();

    void showBooks() const;
    void addBook();
    void removeBook();
    void searchByTitle();
    void searchByAuthor();
    void searchByCategory();
    void showCategories() const;

    bool loadFromFile(const std::string& path);
    bool saveToFile(const std::string& path) const;

private:
    std::vector<Book> books_;
    static std::string toLower(std::string s);
    static bool equalsIgnoreCase(const std::string& a, const std::string& b);
    static bool containsIgnoreCase(const std::string& haystack, const std::string& needle);
};

#endif // LIBRARY_H
