cmake_minimum_required(VERSION 3.31)
project(Matrix C)

set(CMAKE_C_STANDARD 11)

add_library(Matrix STATIC Matrix.c
        Tester.c)
