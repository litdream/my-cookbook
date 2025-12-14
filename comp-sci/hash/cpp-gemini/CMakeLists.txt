cmake_minimum_required(VERSION 3.10)
project(HashTable CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the HashTable library
add_library(hashtable hashtable.cpp hashtable.hpp)

# Add the test executable
add_executable(hashtable_test hashtable_test.cpp)

# Link the test executable with the HashTable library and GTest
target_link_libraries(hashtable_test hashtable ${GTEST_LIBRARIES} pthread)

# Add Google Test discover tests
include(GoogleTest)
gtest_discover_tests(hashtable_test)
