#include "Library.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Library::Library() {
    // Seed with classic literature, Ethereum / blockchain, and information-intelligence titles
    books_ = {
        {"The Hobbit", "J.R.R. Tolkien", 1937, "Classic",
         "Adventure and wisdom from Middle-earth."},
        {"Pride and Prejudice", "Jane Austen", 1813, "Classic",
         "Social intelligence and character insight."},
        {"Clean Code", "Robert C. Martin", 2008, "Software Engineering",
         "Principles for readable, maintainable code."},
        {"Ethereum Whitepaper", "Vitalik Buterin", 2013, "Ethereum",
         "Foundational paper on smart contracts and a world computer."},
        {"Mastering Ethereum", "Andreas M. Antonopoulos", 2018, "Ethereum",
         "Practical guide to Ethereum development and security."},
        {"Artificial Intelligence: A Modern Approach", "Stuart Russell & Peter Norvig", 2020,
         "Information Intelligence",
         "Canonical textbook covering search, knowledge, learning, and agents."},
        {"The Book of Why", "Judea Pearl", 2018, "Information Intelligence",
         "Causal reasoning and the science of cause and effect."},
        {"Superintelligence", "Nick Bostrom", 2014, "Information Intelligence",
         "Paths, dangers, and strategies around advanced AI."},
    };
}

std::string Library::toLower(std::string s) {
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

bool Library::equalsIgnoreCase(const std::string& a, const std::string& b) {
    return toLower(a) == toLower(b);
}

bool Library::containsIgnoreCase(const std::string& haystack, const std::string& needle) {
    return toLower(haystack).find(toLower(needle)) != std::string::npos;
}

void Library::showBooks() const {
    if (books_.empty()) {
        std::cout << "\nThe library is empty.\n";
        return;
    }

    std::cout << "\n=== Library Catalog (" << books_.size() << " books) ===\n";
    for (std::size_t i = 0; i < books_.size(); ++i) {
        const Book& b = books_[i];
        std::cout << i + 1 << ". \"" << b.title << "\" by " << b.author
                  << " (" << b.year << ")\n"
                  << "   Category: " << b.category << "\n";
        if (!b.notes.empty()) {
            std::cout << "   Notes: " << b.notes << "\n";
        }
    }
}

void Library::addBook() {
    Book book;

    std::cout << "\nBook title: ";
    std::getline(std::cin, book.title);

    std::cout << "Author: ";
    std::getline(std::cin, book.author);

    std::cout << "Publication year: ";
    std::string yearText;
    std::getline(std::cin, yearText);

    try {
        std::size_t charactersRead = 0;
        book.year = std::stoi(yearText, &charactersRead);
        if (charactersRead != yearText.size() || book.year < 0) {
            throw std::invalid_argument("year must be a non-negative number");
        }
    } catch (const std::exception&) {
        std::cout << "Please enter a valid year. The book was not added.\n";
        return;
    }

    std::cout << "Category (e.g. Classic, Ethereum, Information Intelligence): ";
    std::getline(std::cin, book.category);
    if (book.category.empty()) {
        book.category = "General";
    }

    std::cout << "Short notes / intelligence summary (optional): ";
    std::getline(std::cin, book.notes);

    if (book.title.empty() || book.author.empty()) {
        std::cout << "Title and author cannot be empty. The book was not added.\n";
        return;
    }

    books_.push_back(book);
    std::cout << "Book added.\n";
}

void Library::removeBook() {
    if (books_.empty()) {
        std::cout << "\nThe library is empty. Nothing to remove.\n";
        return;
    }

    showBooks();
    std::cout << "\nEnter the number of the book to remove (or 0 to cancel): ";
    std::string input;
    std::getline(std::cin, input);

    try {
        std::size_t charactersRead = 0;
        int index = std::stoi(input, &charactersRead);
        if (charactersRead != input.size() || index < 0) {
            throw std::invalid_argument("invalid index");
        }
        if (index == 0) {
            std::cout << "Removal cancelled.\n";
            return;
        }
        if (static_cast<std::size_t>(index) > books_.size()) {
            std::cout << "Invalid book number.\n";
            return;
        }
        const Book removed = books_[static_cast<std::size_t>(index - 1)];
        books_.erase(books_.begin() + (index - 1));
        std::cout << "Removed: \"" << removed.title << "\" by " << removed.author << "\n";
    } catch (const std::exception&) {
        std::cout << "Please enter a valid number.\n";
    }
}

void Library::searchByTitle() {
    std::string wanted;
    std::cout << "\nEnter title (or part of it, case-insensitive): ";
    std::getline(std::cin, wanted);

    if (wanted.empty()) {
        std::cout << "Search term cannot be empty.\n";
        return;
    }

    bool found = false;
    for (const Book& book : books_) {
        if (containsIgnoreCase(book.title, wanted)) {
            if (!found) {
                std::cout << "\nMatching books:\n";
                found = true;
            }
            std::cout << "- \"" << book.title << "\" by " << book.author
                      << " (" << book.year << ") [" << book.category << "]\n";
            if (!book.notes.empty()) {
                std::cout << "  Notes: " << book.notes << "\n";
            }
        }
    }

    if (!found) {
        std::cout << "No book found matching that title.\n";
    }
}

void Library::searchByAuthor() {
    std::string wanted;
    std::cout << "\nEnter author name (or part of it, case-insensitive): ";
    std::getline(std::cin, wanted);

    if (wanted.empty()) {
        std::cout << "Search term cannot be empty.\n";
        return;
    }

    bool found = false;
    for (const Book& book : books_) {
        if (containsIgnoreCase(book.author, wanted)) {
            if (!found) {
                std::cout << "\nMatching books:\n";
                found = true;
            }
            std::cout << "- \"" << book.title << "\" by " << book.author
                      << " (" << book.year << ") [" << book.category << "]\n";
        }
    }

    if (!found) {
        std::cout << "No book found matching that author.\n";
    }
}

void Library::searchByCategory() {
    std::string wanted;
    std::cout << "\nEnter category (e.g. Ethereum, Information Intelligence, Classic):\n"
              << "  (partial match, case-insensitive): ";
    std::getline(std::cin, wanted);

    if (wanted.empty()) {
        std::cout << "Search term cannot be empty.\n";
        return;
    }

    bool found = false;
    for (const Book& book : books_) {
        if (containsIgnoreCase(book.category, wanted)) {
            if (!found) {
                std::cout << "\nBooks in matching categories:\n";
                found = true;
            }
            std::cout << "- \"" << book.title << "\" by " << book.author
                      << " (" << book.year << ") [" << book.category << "]\n";
            if (!book.notes.empty()) {
                std::cout << "  Notes: " << book.notes << "\n";
            }
        }
    }

    if (!found) {
        std::cout << "No books found in a matching category.\n";
    }
}

void Library::showCategories() const {
    if (books_.empty()) {
        std::cout << "\nThe library is empty.\n";
        return;
    }

    std::vector<std::string> cats;
    for (const Book& b : books_) {
        bool already = false;
        for (const std::string& c : cats) {
            if (equalsIgnoreCase(c, b.category)) {
                already = true;
                break;
            }
        }
        if (!already) {
            cats.push_back(b.category);
        }
    }

    std::sort(cats.begin(), cats.end(),
              [](const std::string& a, const std::string& b) {
                  return toLower(a) < toLower(b);
              });

    std::cout << "\n=== Categories in the catalog ===\n";
    for (const std::string& c : cats) {
        int count = 0;
        for (const Book& b : books_) {
            if (equalsIgnoreCase(b.category, c)) {
                ++count;
            }
        }
        std::cout << "- " << c << " (" << count << ")\n";
    }
}

bool Library::loadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }

    std::vector<Book> loaded;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        // Format: title|author|year|category|notes
        std::stringstream ss(line);
        Book b;
        std::string yearStr;
        if (!std::getline(ss, b.title, '|') ||
            !std::getline(ss, b.author, '|') ||
            !std::getline(ss, yearStr, '|') ||
            !std::getline(ss, b.category, '|')) {
            continue;
        }
        std::getline(ss, b.notes);  // rest of line may contain |
        try {
            b.year = std::stoi(yearStr);
            if (b.year < 0) {
                continue;
            }
        } catch (...) {
            continue;
        }
        if (!b.title.empty() && !b.author.empty()) {
            loaded.push_back(b);
        }
    }

    if (!loaded.empty()) {
        books_ = std::move(loaded);
        return true;
    }
    return false;
}

bool Library::saveToFile(const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    out << "# C++ Library Catalog – title|author|year|category|notes\n";
    for (const Book& b : books_) {
        out << b.title << '|' << b.author << '|' << b.year << '|'
            << b.category << '|' << b.notes << '\n';
    }
    return true;
}
