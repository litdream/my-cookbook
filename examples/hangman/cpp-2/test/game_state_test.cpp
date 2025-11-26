#include "gtest/gtest.h"
#include "../game_state.hpp"

// Test fixture for GameState tests to reduce code duplication
class GameStateTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    GameStateTest() : game("hello", "A common greeting") {
        // You can do set-up work for each test here.
    }

    ~GameStateTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test suite for GameState.
    GameState game;
};


// --- DidWin() Tests ---
TEST_F(GameStateTest, DidWin_NoGuesses) {
    EXPECT_FALSE(game.DidWin());
}

TEST_F(GameStateTest, DidWin_PartialGuess) {
    game.ProcessGuess('h');
    game.ProcessGuess('e');
    EXPECT_FALSE(game.DidWin());
}

TEST_F(GameStateTest, DidWin_AllGuessed) {
    game.ProcessGuess('h');
    game.ProcessGuess('e');
    game.ProcessGuess('l');
    game.ProcessGuess('o');
    EXPECT_TRUE(game.DidWin());
}

TEST_F(GameStateTest, DidWin_ExtraGuesses) {
    game.ProcessGuess('h');
    game.ProcessGuess('e');
    game.ProcessGuess('l');
    game.ProcessGuess('o');
    game.ProcessGuess('z'); // incorrect guess
    EXPECT_TRUE(game.DidWin());
}

// --- ProcessGuess() Tests ---

TEST_F(GameStateTest, ProcessGuess_Correct) {
    EXPECT_EQ(game.ProcessGuess('h'), SUCCESS);
    // You'd also want to check that wrong_count is still 0
    // and 'h' is in the guessed list, but we need methods to expose those.
}

TEST_F(GameStateTest, ProcessGuess_Incorrect) {
    EXPECT_EQ(game.ProcessGuess('z'), SUCCESS);
    // You'd also want to check that wrong_count is 1.
}

TEST_F(GameStateTest, ProcessGuess_Duplicate) {
    game.ProcessGuess('h');
    EXPECT_EQ(game.ProcessGuess('h'), DUP_GUESS);
}

TEST_F(GameStateTest, ProcessGuess_DuplicateIncorrect) {
    game.ProcessGuess('z');
    EXPECT_EQ(game.ProcessGuess('z'), DUP_GUESS);
}

TEST_F(GameStateTest, ProcessGuess_NotAlpha) {
    EXPECT_EQ(game.ProcessGuess('5'), NOT_ALPHA);
    EXPECT_EQ(game.ProcessGuess(' '), NOT_ALPHA);
    EXPECT_EQ(game.ProcessGuess('.'), NOT_ALPHA);
}

TEST_F(GameStateTest, ProcessGuess_CaseInsensitive) {
    EXPECT_EQ(game.ProcessGuess('H'), SUCCESS);
    EXPECT_TRUE(game.DidWin() == false); // only 'h' should be revealed
}


// --- GameOver() Tests ---

TEST_F(GameStateTest, GameOver_InProgress) {
    game.ProcessGuess('a');
    game.ProcessGuess('b');
    EXPECT_FALSE(game.GameOver());
}

TEST_F(GameStateTest, GameOver_PlayerWins) {
    game.ProcessGuess('h');
    game.ProcessGuess('e');
    game.ProcessGuess('l');
    game.ProcessGuess('o');
    EXPECT_TRUE(game.GameOver());
}

TEST_F(GameStateTest, GameOver_PlayerLoses) {
    game.ProcessGuess('a');
    game.ProcessGuess('b');
    game.ProcessGuess('c');
    game.ProcessGuess('d');
    game.ProcessGuess('f');
    game.ProcessGuess('g'); // 6 wrong guesses
    game.ProcessGuess('i'); // 7th wrong guess
    EXPECT_TRUE(game.GameOver());
}