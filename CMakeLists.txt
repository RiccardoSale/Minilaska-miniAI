cmake_minimum_required(VERSION 3.17)
project(minilaska_diviso C)

set(CMAKE_C_STANDARD 90)

add_executable(minilaska_diviso main.c find.c find.h campo.c campo.h game_engine.c game_engine.h struct.c struct.h recursive.c recursive.h swap.c swap.h)