#!/usr/bin/env python3

# Script that extracts the 'StaticTask's in use, and then makes sure
# they don't exceed their statically-allocated stack usage.

import sys
from re import findall
from pathlib import Path

print('{:10}{:>15}{:>15}'.format('task', 'allocated', 'used'))
print('----------------------------------------')

tasks = []

# lmao what is this
for filename in Path('src').glob('**/*.cpp'):
    filename = str(filename)
    with open(filename, 'r') as f:
        s = f.read()
        toks = findall(r"[\w']+|[.,!?;]", s)
        for i, t in enumerate(toks):
            if t == 'StaticTask':
                used = None
                with open('CMakeFiles/csdc5-a.elf.dir/{}.su'.format(filename)) as suf:
                    sut = suf.readlines()
                    stoks = map(lambda s: findall(r"[\w\.]+", s), sut)
                    for su in stoks:
                        if toks[i+7] == su[4]:
                            if su[-1] != 'static':
                                print('task {} does not use a static stack size'.format(toks[i+2]))
                                exit(1)
                            used = int(su[-2])
                tasks.append({'name': toks[i+2],
                              'alloc': int(toks[i+1]) * 4,
                              'func': toks[i+7],
                              'file': filename,
                              'used': used})

failed = False
for t in tasks:
    print('{:10}{:>15}{:>15}'.format(t["name"], t["alloc"], t["used"]))
    if (t["alloc"] < t["used"]):
        failed = True

if failed:
    exit(2)
