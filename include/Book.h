#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book {
    std::string title;
    std::string author;
    int year = 0;
    std::string category;   // e.g. "Classic", "Ethereum", "Information Intelligence"
    std::string notes;      // short description / intelligence summary
};

#endif // BOOK_H
