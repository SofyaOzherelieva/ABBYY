#pragma once

#include <cstdio>

const int MAX_ARGC = 4;

enum Command : uint8_t {
#define COMMAND(NUM, NAME, ARGC, CODE) \
NUM,

#include "commands.h"

#undef COMMAND
};

std::map<std::string, Command> StrToCommand = {
#define COMMAND(NUM, NAME, ARGC, CODE) \
  {(NAME), (NUM)},

#include "commands.h"

#undef COMMAND
};

/////////////////////////////////////////////////////

enum Register : uint8_t {
#define REGISTER(NUM, NAME) \
NUM,

#include "registers.h"

#undef REGISTER
};

std::map<std::string, Register> RegisterToStr = {
#define REGISTER(NUM, NAME) \
  {(NAME), (NUM)},

#include "registers.h"

#undef REGISTER
};


/////////////////////////////////////////////////////

struct CCommand {

  CCommand(){};
  CCommand(std::string *parts, size_t argc) :
    name_(parts[0]),
    argc_(argc),
    num_(END) {
    assert("Too many arguments: " && argc < MAX_ARGC);
    for (int i = 0; i < argc; i++) {
#define REGISTER(NUM, NAME) \
  if(parts[i + 1] == (NAME)){ \
    parts[i + 1] = std::to_string((NUM)); \
  }
#include "registers.h"

#undef REGISTER

      argv_[i] = std::stod(parts[i + 1]);
    }
  }

  CCommand &operator=(const CCommand &new_command) {
    argc_ = new_command.argc_;
    for (int i = 0; i < argc_; i++) {
      argv_[i] = new_command.argv_[i];
    }
    name_ = new_command.name_;
    num_  = new_command.num_;
    return *this;
  }


  ~CCommand() noexcept {}

  std::string name_  = "";
  size_t      argc_  = NULL;
  double      argv_[MAX_ARGC];
  Command     num_   = END;

};