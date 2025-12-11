cmake_minimum_required(VERSION 3.10)
project(MaxHeapTest C CXX)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

# Add the maxheap library
add_library(maxheap STATIC maxheap.c)
target_include_directories(maxheap PUBLIC .)

# Add the test executable
add_executable(maxheap_test maxheap_test.cpp)

# Link against maxheap library and Google Test libraries
target_link_libraries(maxheap_test maxheap GTest::gtest GTest::gtest_main)

# Enable testing
enable_testing()
add_test(NAME MaxHeapUnitTests COMMAND maxheap_test)
