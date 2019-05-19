project(AvlTreeLibTests)

add_subdirectory(lib/googletest-release-1.8.1)

include_directories(lib/googletest-release-1.8.1/googletest/include)
include_directories(lib/googletest-release-1.8.1/googlemock/include)

add_library(AvlTreeLibTests TestsRunner.h TestsRunner.cpp AvlTreeTests.cpp)

target_link_libraries(AvlTreeLibTests AvlTreeLib gtest gtest_main)
