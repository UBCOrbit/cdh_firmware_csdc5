cmake -G "MinGW Makefiles"^
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1^
      -DCMAKE_TOOLCHAIN_FILE=./cmake/gcc.cmake .
