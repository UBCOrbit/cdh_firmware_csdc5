#!/bin/sh

export CCC_CC=clang
export CCC_CXX=clang++

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1\
      -DCMAKE_TOOLCHAIN_FILE=./cmake/static.cmake .

# reformat our source code
clang-format -style=file -i src/**/*.cpp src/**/*.h src/**/*.c

# run the linter
clang-tidy src/*

# run the static analyzer
scan-build make -j4
