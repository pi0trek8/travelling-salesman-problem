cmake_minimum_required(VERSION 3.25)
project(travelling-salesman-problem)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(travelling-salesman-problem src/main.cpp
        src/graph/Graph.cpp
        src/graph/Graph.h
        src/algorithms/BruteForce.cpp
        src/algorithms/BruteForce.h
        src/array/Array.h
        src/algorithms/LCBranchAndBound.cpp
        src/algorithms/LCBranchAndBound.h
        src/algorithms/Matrix.cpp
        src/algorithms/Matrix.h
        src/ui/MainMenu.cpp
        src/ui/MainMenu.h
        src/ui/ConsoleHelper.cpp
        src/ui/ConsoleHelper.h
        src/file/FileReader.cpp
        src/file/FileReader.h
        src/timer/Timer.cpp
        src/timer/Timer.h
        src/to/AlgorithmResultTO.cpp
        src/to/AlgorithmResultTO.h
        src/algorithms/Algorithm.h
        src/algorithms/DFSBranchBound.cpp
        src/algorithms/DFSBranchBound.h
        src/ui/RandomGenerator.cpp
        src/ui/RandomGenerator.h
        src/algorithms/DynamicProgramming.cpp
        src/algorithms/DynamicProgramming.h
        src/algorithms/BruteForce2.cpp
        src/algorithms/BruteForce2.h
        src/ui/MenuUtils.cpp
        src/ui/MenuUtils.h)