#!/bin/sh
# kills a program which pid is passed by argument with SIGINT

if [ "$#" -ne 1 ]; then
    printf "Usage: %s <pid>\n" "${0%.*}"
    exit 1
fi

/bin/kill -s SIGQUIT "$1"
