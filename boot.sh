#!/bin/sh

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1\
      -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain.cmake .
