#include <err.h>
#include <fstream>
#include <map>
#include <iostream>
#include "cpu.h"

int main(int argc, const char **argv) {

  if (argc != 3) {
    errx(1, "Exactly 2 arguments expected: binary and decompile files");
  }
  std::ofstream out(argv[2]);
  Cpu::decompile(out, argv[1]);
  out.close();
}