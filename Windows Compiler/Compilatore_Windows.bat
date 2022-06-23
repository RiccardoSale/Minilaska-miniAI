#!/bin/bash
cd ..
cd sorgenti
gcc -pedantic -O3 -Wno-unused-result board.c shift.c main.c game_engine.c find.c recursive.c vector.c -o minilaska.exe
minilaska.exe