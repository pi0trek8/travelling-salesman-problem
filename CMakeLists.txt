cmake_minimum_required(VERSION 3.25)
project(travelling-salesman-problem)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(travelling-salesman-problem src/main.cpp src/main.cpp
        src/graph/Graph.cpp
        src/graph/Graph.h
        src/graph/edge/Edge.cpp
        src/graph/edge/Edge.h
        src/algorithms/BruteForce.cpp
        src/algorithms/BruteForce.h
        src/array/Array.h
        src/result/AlgorithmResult.cpp
        src/result/AlgorithmResult.h)
