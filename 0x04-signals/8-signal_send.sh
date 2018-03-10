#!/bin/bash
# kills a program which pid is passed by argument with SIGINT

if [ "$#" -ne 1 ]; then
    printf "Usage: %s <pid>\n", "$0"
fi

kill -s SIGINT $1
