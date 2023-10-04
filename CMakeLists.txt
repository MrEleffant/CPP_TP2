cmake_minimum_required(VERSION 3.26)
project(CPP_TP2)

set(CMAKE_CXX_STANDARD 23)

add_executable(CPP_TP2
        Sinus.cpp
        sinus_main_test.cpp
        doctest.h
        ComputeParameters.cpp
        ComputeParameters.h)
