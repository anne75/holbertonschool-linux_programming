#!/usr/bin/python3
import ctypes
import sys
"""
this is module read_write_heap
modify the heap of a process
"""


def read_maps(pid):
    """
    Reads a process maps file: finds the heap an prints details.

    :param pid: a process pid
    :return: If heap found a tuple start address of heap, end address
             as integers, else: None
    """
    print("[*] Maps: /proc/{}/Maps".format(pid))
    with open("/proc/{}/maps".format(pid), mode="r", encoding="utf-8") as f:
        for line in f:
            if "[heap]" in line:
                heap_found = True
                print(line)
                break
    line_split = line.split()
    if heap_found:
        print("[*] Found [heap]:")
        print("    pathname = {}".format(line_split[-1]))
        print("    addresses = {}".format(line_split[0]))
        print("    permissions = {}".format(line_split[1]))
        print("    offset = {}".format(line_split[2]))
        print("    inode = {}".format(line_split[-2]))
        addr = line_split[0].split("-")
        print("[*] Addr start [{}] | end [{}]".format(addr[0], addr[1]))
        return int(addr[0], 16), int(addr[1], 16)
    return None


def replace_string(pid, start, end, to_replace, new):
    """
    Finds and replaces a string in a process heap.

    :param pid: process id
    :param start: start address of heap.
    :param end: end address of heap.
    :param to_replace: string to find.
    :param new: string to write in place of to_replace.
    """
    with open("/proc/{}/mem".format(pid), mode="rb") as f:
        f.seek(start)
        chunk = f.read(end - start)
    # work with bytes.
    to_replace_b = to_replace.encode("utf-8")
    new_b = new.encode("utf-8")
    if to_replace_b in chunk:
        print("[*] Found {} at {}".format(to_replace,
                                          hex(chunk.find(to_replace_b))))
        chunk = chunk.replace(to_replace_b, new_b)
        l_t = len(to_replace_b)
        l_n = len(new_b)
        if l_t > l_n:
            chunk = chunk + b"0"*(l_t - l_n)
        elif l_t < l_n:
            chunk = chunk[:-(l_n - l_t)]
        with open("/proc/{}/mem".format(pid), mode="wb") as f:
            f.seek(start)
            f.write(chunk)


def dev_main():
    """
    Entrypoint to read the heap of a process in dev mode.
    """
    import subprocess
    args = subprocess.check_output("ps aux | grep infinite_loop", shell=True)
    if not args:
        exit(1)
    args = str(args).split("\n")
    arg = args[0].split()[1]
    print(arg)

    addresses = read_maps(arg)
    if addresses:
        replace_string(arg, addresses[0], addresses[1], "Moon", "Good Night")


def main():
    """
    Other Entrypoint.
    """
    if len(sys.argv) != 4:
        print(
            "Usage: {} pid search_string replace_string\n"
            "       pid: process id.".format(__file__))
        exit(1)
    addresses = read_maps(sys.argv[1])
    if addresses:
        replace_string(sys.argv[1], addresses[0], addresses[1],
                       sys.argv[2], sys.argv[3])


# Help
# sys.settrace
# http://stackoverflow.com/questions/10035541/
# what-causes-a-python-segmentation-fault
# Partial interface to ptrace(2), only for PTRACE_ATTACH and PTRACE_DETACH.
# http://unix.stackexchange.com/questions/6267/how-to-re-load-all-running-
# applications-from-swap-space-into-ram/6271#6271
# http://unix.stackexchange.com/questions/6301/how-do-i-read-from-proc-pid-
# mem-under-linux

if __name__ == "__main__":
    main()
