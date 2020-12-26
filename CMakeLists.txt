cmake_minimum_required(VERSION 3.17)
project(final_laska C)

set(CMAKE_C_STANDARD 90)

add_executable(final_laska main.c game_engine.c recursive.c struct.c vector.c shift.c find.c board.c)