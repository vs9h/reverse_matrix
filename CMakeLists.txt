cmake_minimum_required(VERSION 3.16)
project(reverse_matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(reverse_matrix main.cpp src/matrix.h src/complex.h src/utils.h)