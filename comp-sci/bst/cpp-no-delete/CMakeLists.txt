cmake_minimum_required(VERSION 3.14)
project(BST_Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BST library
add_library(bst_lib
    bst.cpp
    bst.hpp
)

# Original main executable
add_executable(bst_main main.cpp)
target_link_libraries(bst_main PRIVATE bst_lib)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(bst_test bst_test.cpp)
target_link_libraries(bst_test PRIVATE bst_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bst_test)
