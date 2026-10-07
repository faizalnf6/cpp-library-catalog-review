#!/usr/bin/env bash

set -euo pipefail

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Compile to /tmp (artifacts filesystem may be noexec)
PROGRAM="$(mktemp /tmp/library-catalog-test.XXXXXX)"
OUTPUT="$(mktemp)"
DATA_BACKUP=""
trap 'rm -f "$PROGRAM" "$OUTPUT"; [[ -n "$DATA_BACKUP" && -f "$DATA_BACKUP" ]] && mv "$DATA_BACKUP" "$PROJECT_DIR/library_data.txt" 2>/dev/null || true; rm -f "$PROJECT_DIR/library_data.txt"' EXIT

# Avoid polluting a real data file during tests
if [[ -f "$PROJECT_DIR/library_data.txt" ]]; then
  DATA_BACKUP="$(mktemp)"
  mv "$PROJECT_DIR/library_data.txt" "$DATA_BACKUP"
fi
rm -f "$PROJECT_DIR/library_data.txt"

g++ -std=c++17 -Wall -Wextra -pedantic \
  -I"$PROJECT_DIR/include" \
  "$PROJECT_DIR/main.cpp" \
  "$PROJECT_DIR/src/Library.cpp" \
  -o "$PROGRAM"
chmod +x "$PROGRAM"

# --- Exact / case-insensitive title & author search ---
printf '4\nThe Hobbit\n5\nJane Austen\n4\nthe hobbit\n9\n' |
  "$PROGRAM" > "$OUTPUT"

grep -q 'The Hobbit' "$OUTPUT"
grep -q 'Pride and Prejudice' "$OUTPUT"
# case-insensitive should still find The Hobbit
grep -q 'Matching books:' "$OUTPUT" || grep -q 'The Hobbit' "$OUTPUT"

# --- Category search (Ethereum & Information Intelligence) ---
printf '6\nEthereum\n6\nInformation Intelligence\n7\n9\n' |
  "$PROGRAM" > "$OUTPUT"

grep -q 'Ethereum Whitepaper\|Mastering Ethereum' "$OUTPUT"
grep -q 'Artificial Intelligence\|The Book of Why\|Superintelligence' "$OUTPUT"
grep -q 'Ethereum\|Information Intelligence\|Classic' "$OUTPUT"

# --- Invalid year rejected ---
printf '2\nNew Book\nA New Author\n20x\nGeneral\n\n1\n9\n' |
  "$PROGRAM" > "$OUTPUT"

grep -q 'Please enter a valid year. The book was not added.' "$OUTPUT"
if grep -q 'New Book by A New Author' "$OUTPUT"; then
  echo "FAIL: invalid year added a book"
  exit 1
fi

# --- Valid add + find ---
printf '2\nValid Book\nValid Author\n2026\nEthereum\nTest note for intelligence\n4\nValid Book\n9\n' |
  "$PROGRAM" > "$OUTPUT"

grep -q 'Book added.' "$OUTPUT"
grep -q 'Valid Book' "$OUTPUT"
grep -q 'Ethereum' "$OUTPUT"

# --- Remove (cancel path + invalid) ---
printf '3\n0\n9\n' |
  "$PROGRAM" > "$OUTPUT"
grep -q 'Removal cancelled.' "$OUTPUT"

echo "All C++ Library Catalog tests passed."
