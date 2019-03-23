#!/bin/sh

openocd -f openocd.cfg -c 'program bin/csdc5-a.elf verify reset exit'
