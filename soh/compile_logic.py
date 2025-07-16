#!/usr/bin/env python

from sys import argv

if len(argv) < 1:
    print("expects input file")
    exit()

class RR:
    __slots__ = "name", "scene", "events", "checks", "exits"
    def __init__(self, name, scene):
        self.name = name
        self.scene = scene
        self.events = []
        self.checks = []
        self.exits = []

RRs = []
active_rr = None
buf = ""
open_count = close_count = 0
for line in open(argv[1]):
    if line.startswith("def "):
        if open_count != close_count:
            print("error parsing:", name)
        defline = line.split()
        name = defline[1]
        active_rr = RR(name, defline[2])
        RRs.append(active_rr)
        buf = ""
        open_count = close_count = 0
        continue
    if line.startswith("--"):
        continue
    open_count += line.count('(')
    close_count += line.count(')')
    buf += line
    if open_count != close_count:
        continue
    if buf and buf.isspace(): continue
    try:
        thing, code = buf.split(None, 1)
        code = code.strip()
    except:
        print("failed to parse line", buf)
        continue
    if thing.startswith("RR_"):
        active_rr.exits.append((thing, code))
    elif thing.startswith("RC_"):
        active_rr.checks.append((thing, code))
    else:
        active_rr.events.append((thing, code))
    buf = ""

def gen(code):
    return code

result = []
output = result.append
for rr in RRs:
    output(f"areaTable[{rr.name}] = Region(\"...\", {rr.scene}, {{")
    if rr.events:
        output("\n")
        for name, code in rr.events:
            output(f"\tEventAccess(&logic->{name}, []{{return {gen(code)};}}),\n")
    output("}, {")

    if rr.checks:
        output("\n")
        for name, code in rr.checks:
            output(f"\tLOCATION({name}, {gen(code)}),\n")
    output("}, {")

    if rr.exits:
        output("\n")
        for name, code in rr.events:
            output(f"\tEntrance({name}, []{{return {gen(code)};}}),\n")
    output("});\n")

print("".join(result))
