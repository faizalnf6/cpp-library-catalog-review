# C++ Grob and Deal Review Code
linux supported llp native logic code for organizing book. reviewed under remote phone programming.

---

# C++ Library Catalog  
### Majestic Exarch Edition — Ethereum · Books · Information Intelligence

A beginner-friendly command-line library catalog that manages books across classic literature, **Ethereum / blockchain**, and **information intelligence** (AI, causal reasoning, superintelligence).

## Features

- Show all books (with category + short intelligence notes)
- Add a book (title, author, year, category, notes)
- Remove a book by number
- Search by title (partial, **case-insensitive**)
- Search by author (partial, **case-insensitive**)
- Search by category (e.g. `Ethereum`, `Information Intelligence`, `Classic`)
- List unique categories with counts
- **Persist** the catalog to `library_data.txt` (auto-load on start, save on exit or via menu)

## Sample seed books

| Title | Author | Category |
|-------|--------|----------|
| The Hobbit | J.R.R. Tolkien | Classic |
| Pride and Prejudice | Jane Austen | Classic |
| Clean Code | Robert C. Martin | Software Engineering |
| Ethereum Whitepaper | Vitalik Buterin | Ethereum |
| Mastering Ethereum | Andreas M. Antonopoulos | Ethereum |
| Artificial Intelligence: A Modern Approach | Russell & Norvig | Information Intelligence |
| The Book of Why | Judea Pearl | Information Intelligence |
| Superintelligence | Nick Bostrom | Information Intelligence |

## Build & run

From the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
  -I cpp-library-catalog/include \
  cpp-library-catalog/main.cpp \
  cpp-library-catalog/src/Library.cpp \
  -o cpp-library-catalog/library-catalog

./cpp-library-catalog/library-catalog
```

Or from inside the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -I include main.cpp src/Library.cpp -o library-catalog
./library-catalog
```

## Run the tests

```bash
chmod +x cpp-library-catalog/test.sh
./cpp-library-catalog/test.sh
```

The script compiles the program and checks:

- title / author search (including case-insensitive)
- category search for Ethereum and Information Intelligence
- rejection of invalid years
- successful add + find
- remove cancel path

## Project layout

```
cpp-library-catalog/
├── include/
│   ├── Book.h          # Book data structure
│   └── Library.h       # Library class interface
├── src/
│   └── Library.cpp     # Implementation (search, I/O, persistence)
├── main.cpp            # Menu & program entry
├── test.sh
├── README.md
└── .gitignore
```

## What you can learn

1. `struct Book` groups related fields (title, author, year, category, notes).
2. `class Library` owns a `std::vector<Book>` and provides operations.
3. Case-insensitive matching with a simple `toLower` helper.
4. File persistence with a simple `|`-delimited text format.
5. Separating interface (`.h`) from implementation (`.cpp`).

## Suggested next steps

- Add ISBN / URL fields for Ethereum papers and AI references.
- Fuzzy ranking or “intelligence score” for search results.
- Export filtered catalogs (e.g. all Ethereum books) to CSV.
- Unit tests with a C++ framework (Catch2 / Google Test).
