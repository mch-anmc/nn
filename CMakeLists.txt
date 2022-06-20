cmake_minimum_required(VERSION 3.22)
project(nn)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        nn
        nn/include
        )

add_executable(nn

        main.cpp

        nn/src/matrix.cpp
        nn/src/error.cpp)
