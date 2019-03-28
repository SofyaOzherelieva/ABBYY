#include <err.h>
#include "cpu.h"

int main(int argc, const char **argv) {

  if (argc != 3) {
    errx(1, "Exactly 2 arguments expected: input and binary files");
  }

  Cpu::compile(argv[1], argv[2]);
}