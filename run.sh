#!/bin/bash

if [ -z "$1" ]; then
    echo "Użycie: $0 <liczba_procesow>"
    exit 1
fi

NP=$1

mpicxx gamma.cpp -o gamma -lncurses

mpirun -np $NP ./gamma