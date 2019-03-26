#include "Book.h"

int main(int argv, char *argc[]) {
  assert("Too many arguments" && argv <= 2);
  assert("Too few arguments" && argv >= 2);
  char *filename = argc[1];

  Book book(filename);

  sort(book);
  book.output("sort.txt");

  reverse_sort(book);
  book.output("rev_sort.txt");
  return 0;
}