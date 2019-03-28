#pragma once

#include "parser.h"
#include "CCommand.h"
#include "fstream"

namespace Cpu {

static const int MAXSIZE = static_cast<int>(1e6);
char raw_data[MAXSIZE];

// Compile program to binary file
void compile(const char *in_file, const char *out_file = "myBinFile") {
  CCommand    command;
  std::string program;
  CText        program_text(in_file);

  if (!program_text.book_indexed) {
    program_text.book_index();
  }

  std::vector<std::pair<double, size_t> > from;
  std::map<double, size_t>                to;

  std::vector<std::pair<double, size_t> > from_data;
  std::map<double, size_t>                to_data;

  int i = 0;
  for (i = 0; i < program_text.lines_count(); i++) {
    const std::string command_line = program_text[i]->start_index_;

    if (command_line.empty()) {
      continue;
    }

    if(command_line == ".data"){
      break;
    }

    Parser::command_from_str(command_line, &command);

    if (command.name_[0] == '<' && command.name_[1] == '-' || command.name_ == "CALL") {
      from.emplace_back(command.argv_[0], program.size() + 1); // +1 имя команды
    }

    if(command.name_[0] == '#'){
      from_data.emplace_back(command.argv_[0], program.size() + 1); // +1 имя команды
    }

    program.append(reinterpret_cast<const char *>(&command.num_), sizeof(command.num_));
    program.append(reinterpret_cast<const char *>(command.argv_), sizeof(double) * command.argc_);

    if (command.name_[0] == '-' && command.name_[1] == '>') {
      to.emplace(command.argv_[0], program.size());
    }
  }
  //////////////////////////////////////////////////////////
  program.append(".data", sizeof(char)*5);

  for(int j = i + 1; j < program_text.lines_count(); j++){
    const std::string command_line = program_text[j]->start_index_;

    if (command_line.empty()) {
      continue;
    }
    std::string parts[MAX_ARGC + 1]; // + 1 for command word
    size_t      size = 0;
    Parser::parse_line(command_line, parts, &size);

    int data_num = static_cast<int>(std::stod(parts[0]));
    to_data.emplace(data_num, program.size() + 1);// + 1 for command word

    program.append(reinterpret_cast<const char *>(&data_num), sizeof(command.num_));
    parts[1] += '\n';
    program.append(parts[1]);
  }

  for (const auto &from_ : from) {
    auto to_ = to.find(from_.first);
    assert(to_ != to.end());
    *reinterpret_cast<double *>(&program[from_.second]) = to_->second;
  }

  for (const auto &from_data_ : from_data) {
    auto to_data_ = to_data.find(from_data_.first);
    assert(to_data_ != to.end());
    *reinterpret_cast<double *>(&program[from_data_.second]) = to_data_->second;
  }

  std::ofstream out(out_file);
  out << program;
  out.close();
}


// Decompile binary file
void decompile(std::ostream &out, const char *input_filename = "myBinFile") {
  char text[MAXSIZE];

  size_t size = Parser::read_bin_file(text);

  size_t   position = 0;
  CCommand command;

  do {
    Parser::command_from_bin(text, &command, &position);

    out << command.name_ << " ";
    if(command.name_[0] == '-' or command.name_[1] == '>'){
      out << position << " ";
    } else {
      for (int i = 0; i < command.argc_; ++i) {
        out << command.argv_[i] << " ";
      }
    }
    out << "\n";
    // find data section:
    if(text[position] == '.'){
      for (int i = 0; i < 5; i++) {
        out << text[position];
        position += 1;
      }
      out << '\n';
      break;
    }
  } while (position < size);

  do{
    out << position + 1 << " ";
    position++;
    while(text[position] != '\n'){
      out << text[position];
      position++;
    }
    position++;
    out << "\n";
  }while (position < size);
}

#define START_RAM 4e5


void PushInRam(int id, int num) {
  *reinterpret_cast<int *>(raw_data + (int)START_RAM + id * sizeof(int)) = num;
}


int GetFromRam(int id) {
  return *reinterpret_cast<int *>(raw_data + (int)START_RAM + id * sizeof(int));
}

class CStack {
  public:

    explicit CStack(char *start) : start_(start) {}

    void Push(int x) {
      curr_ind += 1;
      *reinterpret_cast<int *>(start_ + curr_ind*sizeof(int)) = x;
    }

    void Pop() {
      curr_ind -= 1;
    }

    int PeekRemove() {
      auto x = *reinterpret_cast<int *>(start_ + curr_ind*sizeof(int));
      curr_ind -= 1;
      return x;
    }

    bool IsEmpty(){
      return curr_ind == 0;
    }

    void Print(){
      for(int i = 1; i <= curr_ind; i++){
        std::cout << *reinterpret_cast<int *>(start_ + i*sizeof(int)) << " ";
      }
      std::cout << '\n';
    }

  private:
    char *start_;
    int curr_ind = 0;
};

// Run program from binary file
void run(const char *input_filename = "myBinFile") {
  const int PROC_STACK_START = static_cast<int>(2e5);
  const int FUNC_STACK_START = static_cast<int>(1e5);

  CStack stack(raw_data + PROC_STACK_START);
  CStack return_pos(raw_data + FUNC_STACK_START);

  Parser::read_bin_file(raw_data);

  size_t   position = 0;
  CCommand command;
  do {
//    stack.Print();
//    std::cout << "RAX: "<< GetFromRam(0) << "RBX: " << GetFromRam(1) << '\n';
    Parser::command_from_bin(raw_data, &command, &position);
    switch (command.num_) {

#define COMMAND(NUM, NAME, ARGC, CODE) \
                case (NUM): \
                    CODE \
                    break;

#include "commands.h"

#undef COMMAND
    }
  } while (command.num_ != END);
}
}