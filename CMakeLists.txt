cmake_minimum_required(VERSION 3.17)
project(PGSTL)

set(CMAKE_CXX_STANDARD 20)

add_executable(PGSTL main.cpp src/RichList.h src/Range.h)