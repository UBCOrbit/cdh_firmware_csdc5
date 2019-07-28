#!/usr/bin/env python3

# Script that extracts the 'StaticTask's in use, and then makes sure
# they don't exceed their statically-allocated stack usage.

import sys
from re import findall
from pathlib import Path

print(f'{"task":10}{"allocated":>15}{"used":>15}')
print('----------------------------------------')

tasks = []

# lmao what is this
for filename in Path('src').glob('**/*.cpp'):
    with open(filename, 'r') as f:
        s = f.read()
        toks = findall(r"[\w']+|[.,!?;]", s)
        for i, t in enumerate(toks):
            if t == 'StaticTask':
                used = None
                with open(f'CMakeFiles/csdc5-a.elf.dir/{filename}.su') as suf:
                    sut = suf.readlines()
                    stoks = map(lambda s: findall(r"[\w\.]+", s), sut)
                    for su in stoks:
                        if toks[i+7] == su[4]:
                            if su[-1] != 'static':
                                print(f'task {toks[i+2]} does not use a static stack size')
                                exit(1)
                            used = int(su[-2])
                tasks.append({'name': toks[i+2],
                              'alloc': int(toks[i+1]) * 4,
                              'func': toks[i+7],
                              'file': filename,
                              'used': used})

failed = False
for t in tasks:
    print(f'{t["name"]:10}{t["alloc"]:>15}{t["used"]:>15}')
    if (t["alloc"] < t["used"]):
        failed = True

if failed:
    exit(2)
