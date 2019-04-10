#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <setjmp.h>


enum Exception : uint8_t {
  BAD_FILE      = 1,
  OUT_OF_MEMORY = 2
};

std::map<Exception, std::string> NumToExceptionName = {
  {BAD_FILE,      "BAD_FILE"},
  {OUT_OF_MEMORY, "OUT_OF_MEMORY"}
};

class Counter;

std::vector<Counter *> current_objects;

std::vector<jmp_buf *> current_jumps;
int                    remain_objects               = 0;
int                    current_exception            = NULL;

class Counter {
  public:
    Counter() {
      current_objects.push_back(this);
      num++;
      std::cout << "CREATE OBJECT: " << num << "\n";
    }

    virtual ~Counter() {
      std::cout << "DELETE OBJECT: " << num << "\n";
      num--;
    }

  private:
    static int num;
};

void Clear() {
  for (int i = remain_objects; i < current_objects.size(); i++) {
    current_objects[i]->~Counter();
  }
}

#define TRY(CODE)                                                           \
  remain_objects = current_objects.size();                                  \
  jmp_buf jump_buffer{};                                                    \
  if (setjmp(jump_buffer) == 0) {                                           \
    current_jumps.push_back(&jump_buffer);                                  \
    CODE                                                                    \
  }\
  current_jumps.pop_back();\

#define CATCH(TYPE) \
  if (current_exception == TYPE){\
    std::cout << "CATCH: " << NumToExceptionName[TYPE] << "\n"; \
  }       \

#define THROW(TYPE)                                                \
  if (current_jumps.size() == 0 or TYPE == NULL) {                \
    exit(1);                                                        \
  }                                                                \
  Clear(); \
  current_exception = TYPE;                                       \
  longjmp(*(current_jumps.back()), TYPE);                        \
