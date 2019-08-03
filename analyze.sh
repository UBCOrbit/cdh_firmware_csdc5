#!/bin/sh

set -e
./clean.sh

export CCC_CC=clang
export CCC_CXX=clang++

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1\
      -DCMAKE_TOOLCHAIN_FILE=./cmake/static.cmake -G Ninja .

# run the linter
clang-tidy-8 --version
clang-tidy-8 -header-filter='.*' src/**/*.cpp src/**/*.h
