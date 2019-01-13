#!/bin/sh

# run cmake, point it towards the toolchain file, and emit a
# compile_commands.json for use with clang autocompletion tooling
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1\
      -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain.cmake .
