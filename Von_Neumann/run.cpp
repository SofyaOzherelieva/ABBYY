#include <err.h>
#include "cpu.h"

int main(int argc, const char **argv) {

  if (argc != 2) {
    errx(1, "Exactly 1 arguments expected: binary file");
  }
  Cpu::run(argv[1]);
}