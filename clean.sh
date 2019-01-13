#!/bin/sh

if [ -f Makefile ]
then
    make clean
    rm Makefile
fi

if [ -f CMakeCache.txt ]
then
    rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake compile_commands.json
fi

if [ -d bin ]
then
    rm -rf bin
fi
