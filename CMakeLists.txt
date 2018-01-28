cmake_minimum_required(VERSION 3.8)
project(PGM)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c lib.h lib.c)
add_executable(PGM ${SOURCE_FILES} lib.h lib.c)