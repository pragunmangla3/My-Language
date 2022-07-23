cmake_minimum_required(VERSION 3.22)
project(simpleparser)

set(CMAKE_CXX_STANDARD 20)

add_executable(simpleparser main.cpp Tokenizer.cpp Tokenizer.h)
