cmake_minimum_required(VERSION 3.16)
project(final_laska C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")

add_executable(final_laska main.c game_engine.c recursive.c struct.c vector.c shift.c find.c board.c)