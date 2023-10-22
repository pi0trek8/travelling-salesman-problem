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
        src/algorithms/BranchAndBound.cpp
        src/algorithms/BranchAndBound.h
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
        src/to/AlgorithmResultTO.h src/algorithms/Algorithm.h)

