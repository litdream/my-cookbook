cmake_minimum_required(VERSION 3.11)
project(HangmanTests)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 14)

# --- Google Test Setup (Auto-Download) ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Prevent Google Test from overriding parent project compiler settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 1. Compile the C logic
add_library(hangman_lib hangman.c)

# 2. Compile the C++ Test Suite
add_executable(run_tests hangman_test.cpp)

# 3. Link them together
# Note: gtest_main includes the main() entry point for tests
target_link_libraries(run_tests hangman_lib gtest_main)
