cmake_minimum_required(VERSION 3.14)
project(BST_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BST library
add_library(bst STATIC
    bst.cpp
    bst.hpp
)

# Main executable (demo)
add_executable(bst_demo
    main.cpp
)
target_link_libraries(bst_demo PRIVATE bst)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(bst_test
    bst_test.cpp
)
target_link_libraries(bst_test PRIVATE bst gtest_main)

include(GoogleTest)
gtest_discover_tests(bst_test)
