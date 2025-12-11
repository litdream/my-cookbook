cmake_minimum_required(VERSION 3.10)
project(MaxHeapTests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Google Test
find_package(GTest CONFIG REQUIRED)

# Add the MaxHeap library
add_library(MaxHeap maxheap.cpp maxheap.hpp)

# Add the test executable
add_executable(maxheap_test maxheap_test.cpp)

# Link MaxHeap and GTest to the test executable
target_link_libraries(maxheap_test PRIVATE MaxHeap GTest::gtest_main GTest::gtest)

# Discover tests automatically
include(GoogleTest)
gtest_discover_tests(maxheap_test)
