## Виртуальная машина построенная на архитектуре фон Неймана

#### cpu.h:

1. Assembler:

Converts assembler code to binary.

Run assembler:

`g++ compile.cpp -o compile`

`./compile <file with assembler code> <output file>`

Example:

`./compile inputRecFib myBinFile`

2. Disassembler:

Converts binary code to assembler.

Run disassembler:

`g++ decompile.cpp -o decompile`

`./decompile <binary file with code> <output file>`

Example:

`./decompile myBinFile myDecompFile`

3. Virtual machine:

Execute binary code.

Run virtual machine:

`g++ run.cpp -o run`

`./run <binary file with code>`

Example:

`./run myBinFile`


#### Supports:
* recursion
* text output
* statically allocated data
* function calls


#### Command descriptions are contained in commands.h
