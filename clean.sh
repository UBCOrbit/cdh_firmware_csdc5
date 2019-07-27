#!/bin/sh

# get the makefile to remove binaries
if [ -f Makefile ]
then
    make clean
    rm Makefile
fi

if [ -f build.ninja ]
then
    ninja clean
    rm -f build.ninja rules.ninja .ninja_deps .ninja_log
fi

# delete cmake's mess
if [ -f CMakeCache.txt ]
then
    rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake compile_commands.json
fi

# delete bin
if [ -d bin ]
then
    rm -rf bin
fi

# delete doxygen documentation
if [ -d docs/doxy ]
then
    rm -rf docs/doxy
fi
