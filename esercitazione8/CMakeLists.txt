cmake_minimum_required(VERSION 3.20)
project(esercitazione8)

# Standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Eseguibili dei test
add_executable(test_un_edge  test_un_edge.cpp)
add_executable(test_un_graph test_un_graph.cpp)

# Registrazione presso CTest
enable_testing()
add_test(NAME test_un_edge  COMMAND test_un_edge)
add_test(NAME test_un_graph COMMAND test_un_graph)