cmake_minimum_required(VERSION 3.10)
project(LListProject)

# --- Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set standard C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library for our linked list implementation.
# This allows us to link it to multiple executables if needed.
add_library(llist llist.cpp llist.hpp)

# Add the test executable.
add_executable(llist_gtest llist_gtest.cpp)

# Link our test executable against our llist library and Google Test.
# gtest_main automatically links against gtest, gmock, and pthread,
# and provides a main() function, so we don't have to write one.
target_link_libraries(llist_gtest llist gtest_main)

# Include the Google Test directory so CMake can find the gtest headers.
include(GoogleTest)

# Discover and add tests to be run by CTest.
enable_testing()
add_test(NAME LListTests COMMAND llist_gtest)
