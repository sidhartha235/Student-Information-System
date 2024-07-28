#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: ./run.sh -input <input_file_name>"
    exit 1
fi

if [ "$1" != "-input" ]; then
    echo "Usage: ./run.sh -input <input_file_name>"
    exit 1
fi

command_args=("$@")

gcc -o 08_19 src/*.c -I./includes

if [ $? -eq 0 ]; then
    echo "Compilation Successful"
    ./08_19 "${command_args[@]}"
else
    echo "Compilation Failed"
fi