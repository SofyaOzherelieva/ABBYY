#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <functional>

struct Line {
  /// Начало строки
  char *start_index_{nullptr};
};

class CText {
  public:
    explicit CText(const char *filename);

    ~CText();

    /// Обращение по строке
    Line *operator[](int i) const;

    /// Кол-во строк в тексте
    size_t lines_count() const;

    bool book_indexed{false};

    void book_index();

  private:
    /// Дескриптор файла, в котором лежит книга.
    FILE *book_{nullptr};

    /// Буффер для хранения текста в памяти.
    char *buffer_{nullptr};

    /// Размер книги в байтах.
    size_t book_size_{0};

    void newline_to_eol();

    /// Массив указателей на строки.
    Line *array_of_lines_{nullptr};

    /// Количество строк.
    size_t num_of_lines_{0};
};

CText::CText(const char *filename) {
  book_ = fopen(filename, "rb");

  if (!book_) {
    perror("fopen");
  };

  fseek(book_, 0, SEEK_END);
  book_size_ = static_cast<size_t>(ftell(book_));
  rewind(book_);

  assert("CText is empty" && book_size_ != 0);

  buffer_ = (char *) malloc(sizeof(char) * (book_size_ + 2));

  assert("Memory allocation error" && buffer_ != nullptr);

  // добавили '\0' в начало, чтобы не прописывать случаи в сравнении с конца
  buffer_[0] = '\0';
  if (fread(buffer_ + sizeof(char), sizeof(char), static_cast<size_t>(book_size_), book_) != book_size_) {
    perror("fread");
  };
  // добавили '\0' в начало
  book_size_++;
}

CText::~CText() {
  fclose(book_);
  free(buffer_);
  free(array_of_lines_);
};

Line *CText::operator[](int i) const{
  assert("CText is not indexed!" && array_of_lines_);

  assert("Выход за границы массива" && i < num_of_lines_);

  return array_of_lines_ + i;
}

size_t CText::lines_count() const {
  assert("CText is not indexed!" && array_of_lines_);

  return num_of_lines_;
}

void CText::book_index() {
  book_indexed = true;
  int index = 0;
  newline_to_eol();

  array_of_lines_ = (Line *) malloc(sizeof(Line) * num_of_lines_);

  assert("Memory allocation error" && array_of_lines_ != nullptr);

  // не учитываем первый символ '\0'
  array_of_lines_[index].start_index_ = buffer_ + 1;

  // не учитываем первый и последний символ '\0'
  for (int i = 1; i < book_size_ - 1; i++) {
    if (buffer_[i] == '\0') {
      index++;
      array_of_lines_[index].start_index_ = buffer_ + i + 1;
    }
  }
}

void CText::newline_to_eol() {
  for (int i = 0; i < book_size_; i++) {
    if (buffer_[i] == '\n') {
      num_of_lines_++;
      buffer_[i] = '\0';
    }
  }
  num_of_lines_++;
}