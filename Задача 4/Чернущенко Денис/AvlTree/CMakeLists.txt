cmake_minimum_required(VERSION 3.14)
project(AvlTree)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}/AvlTreeLib")
include_directories ("${PROJECT_SOURCE_DIR}/AvlTreeLibTests")
include_directories(AvlTreeLibTests/lib/googletest-release-1.8.1/googletest/include)
include_directories(AvlTreeLibTests/lib/googletest-release-1.8.1/googlemock/include)

add_subdirectory (AvlTreeLib)
add_subdirectory(AvlTreeLibTests)

add_executable(AvlTree main.cpp AvlTreeLibTests/AvlTreeTests.cpp)
target_link_libraries (AvlTree AvlTreeLib AvlTreeLibTests)
