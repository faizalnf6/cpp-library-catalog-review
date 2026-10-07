#include "Library.h"

#include <iostream>
#include <string>

namespace {
const std::string kDataFile = "library_data.txt";

void showMenu() {
    std::cout << "\n=== Majestic Library Catalog ===\n"
              << "  (Ethereum · Books · Information Intelligence)\n"
              << "1. Show all books\n"
              << "2. Add a book\n"
              << "3. Remove a book\n"
              << "4. Search by title\n"
              << "5. Search by author\n"
              << "6. Search by category\n"
              << "7. List categories\n"
              << "8. Save catalog to file\n"
              << "9. Exit\n"
              << "Choose an option: ";
}
}  // namespace

int main() {
    Library library;

    if (library.loadFromFile(kDataFile)) {
        std::cout << "Loaded previous catalog from " << kDataFile << ".\n";
    } else {
        std::cout << "Starting with built-in sample books "
                     "(Classic, Ethereum, Information Intelligence).\n";
    }

    while (true) {
        showMenu();

        std::string choice;
        if (!std::getline(std::cin, choice)) {
            std::cout << "\nInput ended. Saving and goodbye!\n";
            library.saveToFile(kDataFile);
            break;
        }

        if (choice == "1") {
            library.showBooks();
        } else if (choice == "2") {
            library.addBook();
        } else if (choice == "3") {
            library.removeBook();
        } else if (choice == "4") {
            library.searchByTitle();
        } else if (choice == "5") {
            library.searchByAuthor();
        } else if (choice == "6") {
            library.searchByCategory();
        } else if (choice == "7") {
            library.showCategories();
        } else if (choice == "8") {
            if (library.saveToFile(kDataFile)) {
                std::cout << "Catalog saved to " << kDataFile << ".\n";
            } else {
                std::cout << "Could not save to " << kDataFile << ".\n";
            }
        } else if (choice == "9") {
            if (library.saveToFile(kDataFile)) {
                std::cout << "Catalog saved. Goodbye!\n";
            } else {
                std::cout << "Goodbye! (could not save catalog)\n";
            }
            break;
        } else {
            std::cout << "Please choose a number from 1 to 9.\n";
        }
    }

    return 0;
}
