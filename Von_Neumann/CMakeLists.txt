cmake_minimum_required(VERSION 3.9)
project(Von_Neumann)

set(CMAKE_CXX_STANDARD 11)

add_executable(Von_Neumann
        ../Onegin_sort/Book.h main.cpp cpu.h parser.h commands.h registers.h CCommand.h compile.cpp Text.h)