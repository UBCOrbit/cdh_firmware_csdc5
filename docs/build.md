# Building

These instructions are for Linux right now, but will be updated with
instructions for windows eventually.

```
./boot.sh
make
```

The generated binary will be placed in `bin/csdc5.bin`.  To clean up,
run:

```
./clean.sh
```
## Requirements

- cmake
- make
- gcc-arm-none-eabi-gcc
- gcc-arm-none-eabi-newlib
