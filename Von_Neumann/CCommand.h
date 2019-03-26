#pragma once

#include <cstdio>

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

  explicit CCommand(std::string name = "",
                    size_t argc = NULL,
                    double *argv = nullptr) : name_(name),
                                              argc_(argc),
                                              argv_(argv),
                                              num_(StrToCommand[name_]) {}

  CCommand(std::string *parts, size_t argc) :
    name_(parts[0]),
    argc_(argc),
    argv_(new double[argc]),
    num_(END) {
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
    argv_ = new double[argc_];
    for (int i = 0; i < argc_; i++) {
      argv_[i] = new_command.argv_[i];
    }
    name_ = new_command.name_;
    num_  = new_command.num_;
    return *this;
  }


  ~CCommand() noexcept {
    delete[] argv_;
  }

  std::string name_  = "";
  size_t      argc_  = NULL;
  double      *argv_ = nullptr;
  Command     num_   = END;

};