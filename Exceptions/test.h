#pragma once

#include "exceptions.h"

int Counter::num = 0;

class Object : public Counter {
  public:
    int object = 1;

    void f(){
      std::cout << object;
    };
};

//// Поимка исклюсения и удаление объектов
void Test1() {
  Exception  type = BAD_FILE;
  TRY(
    Object a;
  std::cout << "TRY: 1\n";
  std::cout << "THROW: " << NumToExceptionName[type] << "\n";
  THROW(type);
  )
  CATCH(type);
}

//// Пролет исключения
void Test2() {
  Exception type1 = BAD_FILE;
  Exception type2 = OUT_OF_MEMORY;
  TRY(
    std::cout << "TRY: 1\n";
  TRY(
    std::cout << "TRY: 2\n";
  std::cout << "THROW: " << NumToExceptionName[type1] << "\n";
  THROW(type1);
  ) CATCH(type2);
  )
  CATCH(type1);
}

//// Пролет исключения и удаление объектов
void Test3() {
  Exception  type1 = BAD_FILE;
  Exception  type2 = OUT_OF_MEMORY;
  TRY(
    std::cout << "TRY: 1\n";
  Object a;
  Object b;
  TRY(
    Object c;
  Object d;
  std::cout << "TRY: 2\n";
  std::cout << "THROW: " << NumToExceptionName[type1] << "\n";
  THROW(type1);
  ) CATCH(type1);
  )
  CATCH(type2);
}


//// Не поймали исключение:
void Test4() {
  Exception  type1 = BAD_FILE;
  Exception  type2 = OUT_OF_MEMORY;
  TRY(
    std::cout << "TRY\n";
  Object a;
  std::cout << "THROW: " << NumToExceptionName[type1] << "\n";
  THROW(type1);
  )
  CATCH(type2);
}

void run_all_tests() {
  Test1();
  std::cout << "-----------------\n";
  Test2();
  std::cout << "-----------------\n";
  Test3();
  std::cout << "-----------------\n";
  Test4();
  std::cout << "-----------------\n";
};