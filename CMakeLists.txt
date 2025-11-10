cmake_minimum_required(VERSION 4.0)
project(ece463_proj2)

set(CMAKE_CXX_STANDARD 20)

add_executable(sim main.cpp
        BranchPredictor.cpp
        BranchPredictor.h)
