cmake_minimum_required(VERSION 3.28)
project(Graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(Graphs main.cpp
        myQueue.cpp
        myVector.cpp
        myNode.cpp
        arrQueue.cpp)
