cmake_minimum_required(VERSION 3.10)
project(Hangman)

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


set(CMAKE_CXX_STANDARD 11)

# --- Game Executable
add_executable(hangman main.cpp game_state.cpp)


# --- Test Executable
enable_testing()
add_executable(
  game_state_test
  test/game_state_test.cpp
  game_state.cpp
)
target_link_libraries(
  game_state_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(game_state_test)
