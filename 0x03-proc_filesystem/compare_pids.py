#!/usr/bin/env python3
"""
Very simple script to compare the pids in a system obtained 2 different ways.
"""

import subprocess

# Run bash commands
proc = subprocess.check_output(["ls", "/proc/"]).decode("utf-8").split("\n")
ps_aux = subprocess.check_output(["ps", "aux"]).decode("utf-8").split("\n")

# Extract all the pids from the ls /proc command
pids_in_proc = sorted([x for x in proc if x.isdigit()], key=lambda x: int(x))

# Extract all the pids from the ps command
pids_in_ps_aux = sorted([s.split()[1] for s in ps_aux[1:] if len(s) > 1],
                        key=lambda x: int(x))

# The above lists are sorted, I can compare term by term
print("Number of pids for ls /proc: {} and ps: {}".format(
    len(pids_in_proc), len(pids_in_ps_aux)))
for x, y in zip(pids_in_proc, pids_in_ps_aux):
    if x != y:
        print("pids differ for {} and {}".format(x, y))
