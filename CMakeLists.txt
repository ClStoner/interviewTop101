cmake_minimum_required(VERSION 3.10)
project(template)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

add_executable(LinkList             src/LinkList.cpp)
add_executable(DynamicProgramming   src/DynamicProgramming.cpp)
add_executable(BinarySearch         src/BinarySearch.cpp)