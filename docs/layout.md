# Repository Layout

```
.
├── boot.sh                Script to run CMake with the correct options for makefiles.
├── clean.sh               Script to clear CMake's mess and return you to a blank slate.
├── cmake
│   └── toolchain.cmake    CMake configuration file that points it towards gcc-arm-none-gcc.
├── CMakeLists.txt         Main build script.
├── docs                   All documentation files (in markdown) should go here).
│   ├── build.md           A short tutorial on how to build the project.
│   ├── git-workflow.md    A short tutorial on how to work with our git workflow.
│   └── layout.md          This file.
├── mem.ld                 The linker script that organizes how the compiled binary is
│                          layed out in memory on the chip.
├── README.md
└── src                    Main source directory (use .cpp by default).
    ├── isr_vec.s          Interrupt vector with pointers to all handlers.
    ├── main.cpp           Main startup code, in C++.
    └── startup.s          Low-level startup code, in assembly.
```
