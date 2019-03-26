#include <err.h>
#include <fstream>
#include <map>
#include <iostream>
#include "cpu.h"

int main(int argc, const char **argv) {

  if (argc != 3) {
    errx(1, "Exactly 2 arguments expected: input and output file");
  }

  Cpu::compile(argv[1]);
  Cpu::run();

  std::ofstream out(argv[2]);
  Cpu::decompile(out);
  out.close();
}