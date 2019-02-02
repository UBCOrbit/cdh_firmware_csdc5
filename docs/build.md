# Windows

## Requirements

- [VS Code](https://code.visualstudio.com/) (or an editor of your
  choice)
- [CMake](https://cmake.org/): during the installation, make sure to
  add `cmake` to your `PATH`.
- [mingw-w64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download):
  you will need to manually add the `bin` directory to your system `PATH`.
- [arm-none-eabi-gcc](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads):
  add the `bin` directory to your `PATH`.
- [openocd](http://gnutoolchains.com/arm-eabi/openocd/)

## Building

Once all the necessary tools are in place, you can double-click
`boot.bat` in the root of the repository to generate a makefile.
Autocompletion and building should come pre-configure for VS Code (hit
`CTRL-SHIFT-B` to build, and run the "flash" task to flash).  To build
from a command prompt, just run:

```
mingw32-make
```

To debug, you need to have an openocd instance attached to your board.
To do this, open a command prompt in the root of the repository (you
can do this from VS Code), and start the server:

```
openocd -f openocd.cfg
```

Once this is done, you can remotely debug the board using GDB through
VS Code.

# Linux

## Requirements

- cmake
- make
- gcc-arm-none-eabi-gcc
- gcc-arm-none-eabi-newlib
- openocd

## Building

```
./boot.sh
make
```

The generated binary will be placed in `bin/csdc5.bin`.  To clean up,
run:

```
./clean.sh
```
