#include <gtest/gtest.h>
#include <cstring>
#include "hangman.h"

// Test the random word selector
TEST(HangmanLogicTest, ChooseWordValidity) {
    WordHint selection;

    // Run it multiple times to ensure we don't crash
    for(int i=0; i<50; i++) {
        choose_word(&selection);

        // Assert the word is not empty
        EXPECT_GT(strlen(selection.word), 0);
        EXPECT_GT(strlen(selection.hint), 0);

        // Verify the word actually exists in our database
        bool exists = false;
        for(int j=0; j<NUM_WORDS; j++) {
            if(strcmp(selection.word, words[j].word) == 0) {
                exists = true;
                break;
            }
        }
        EXPECT_TRUE(exists) << "Selected word " << selection.word << " is not in the source array.";
    }
}

// Test that choose_word returns 0 (success)
TEST(HangmanLogicTest, ChooseWordReturnValue) {
    WordHint selection;
    int result = choose_word(&selection);

    EXPECT_EQ(result, 0) << "choose_word should return 0 on success";
}

// Test that the selected word has a matching hint
TEST(HangmanLogicTest, ChooseWordHintMatches) {
    WordHint selection;

    // Run multiple times to check different random selections
    for(int i=0; i<20; i++) {
        choose_word(&selection);

        // Find the word in the array and verify hint matches
        bool found_match = false;
        for(int j=0; j<NUM_WORDS; j++) {
            if(strcmp(selection.word, words[j].word) == 0) {
                EXPECT_STREQ(selection.hint, words[j].hint)
                    << "Hint doesn't match for word: " << selection.word;
                found_match = true;
                break;
            }
        }
        EXPECT_TRUE(found_match);
    }
}

// Test char_in_secret function
TEST(HangmanLogicTest, CharInSecretFound) {
    GameState state;
    char secret[] = "python";
    state.secret = secret;
    state.len_secret = strlen(secret);

    // Test characters that exist in the word
    EXPECT_TRUE(char_in_secret(&state, 'p'));
    EXPECT_TRUE(char_in_secret(&state, 'y'));
    EXPECT_TRUE(char_in_secret(&state, 't'));
    EXPECT_TRUE(char_in_secret(&state, 'h'));
    EXPECT_TRUE(char_in_secret(&state, 'o'));
    EXPECT_TRUE(char_in_secret(&state, 'n'));
}

TEST(HangmanLogicTest, CharInSecretNotFound) {
    GameState state;
    char secret[] = "python";
    state.secret = secret;
    state.len_secret = strlen(secret);

    // Test characters that don't exist in the word
    EXPECT_FALSE(char_in_secret(&state, 'a'));
    EXPECT_FALSE(char_in_secret(&state, 'z'));
    EXPECT_FALSE(char_in_secret(&state, 'x'));
    EXPECT_FALSE(char_in_secret(&state, 'q'));
}

TEST(HangmanLogicTest, CharInSecretCaseSensitive) {
    GameState state;
    char secret[] = "python";
    state.secret = secret;
    state.len_secret = strlen(secret);

    // Test uppercase letters (should not match lowercase secret)
    EXPECT_FALSE(char_in_secret(&state, 'P'));
    EXPECT_FALSE(char_in_secret(&state, 'Y'));
}

TEST(HangmanLogicTest, CharInSecretEmptyWord) {
    GameState state;
    char secret[] = "";
    state.secret = secret;
    state.len_secret = 0;

    // Should return false for any character in empty word
    EXPECT_FALSE(char_in_secret(&state, 'a'));
    EXPECT_FALSE(char_in_secret(&state, 'z'));
}

TEST(HangmanLogicTest, CharInSecretSingleChar) {
    GameState state;
    char secret[] = "a";
    state.secret = secret;
    state.len_secret = 1;

    EXPECT_TRUE(char_in_secret(&state, 'a'));
    EXPECT_FALSE(char_in_secret(&state, 'b'));
}

TEST(HangmanLogicTest, CharInSecretRepeatedChars) {
    GameState state;
    char secret[] = "letter";
    state.secret = secret;
    state.len_secret = strlen(secret);

    // 't' appears twice, 'e' appears twice - should still return true
    EXPECT_TRUE(char_in_secret(&state, 't'));
    EXPECT_TRUE(char_in_secret(&state, 'e'));
    EXPECT_TRUE(char_in_secret(&state, 'l'));
    EXPECT_TRUE(char_in_secret(&state, 'r'));
}

// Test char_already_guessed function
TEST(HangmanLogicTest, CharAlreadyGuessedEmpty) {
    GameState state;
    state.guess_count = 0;

    // No guesses yet - should return false for any character
    EXPECT_FALSE(char_already_guessed(&state, 'a'));
    EXPECT_FALSE(char_already_guessed(&state, 'z'));
    EXPECT_FALSE(char_already_guessed(&state, 'x'));
}

TEST(HangmanLogicTest, CharAlreadyGuessedSingleGuess) {
    GameState state;
    state.guessed[0] = 'a';
    state.guess_count = 1;

    // 'a' was guessed
    EXPECT_TRUE(char_already_guessed(&state, 'a'));

    // Other characters were not guessed
    EXPECT_FALSE(char_already_guessed(&state, 'b'));
    EXPECT_FALSE(char_already_guessed(&state, 'z'));
}

TEST(HangmanLogicTest, CharAlreadyGuessedMultipleGuesses) {
    GameState state;
    state.guessed[0] = 'p';
    state.guessed[1] = 'y';
    state.guessed[2] = 't';
    state.guessed[3] = 'h';
    state.guess_count = 4;

    // All guessed characters should return true
    EXPECT_TRUE(char_already_guessed(&state, 'p'));
    EXPECT_TRUE(char_already_guessed(&state, 'y'));
    EXPECT_TRUE(char_already_guessed(&state, 't'));
    EXPECT_TRUE(char_already_guessed(&state, 'h'));

    // Non-guessed characters should return false
    EXPECT_FALSE(char_already_guessed(&state, 'o'));
    EXPECT_FALSE(char_already_guessed(&state, 'n'));
    EXPECT_FALSE(char_already_guessed(&state, 'a'));
}

TEST(HangmanLogicTest, CharAlreadyGuessedFullAlphabet) {
    GameState state;

    // Fill with all lowercase letters
    for(int i = 0; i < NUM_ALPHABET; i++) {
        state.guessed[i] = 'a' + i;
    }
    state.guess_count = NUM_ALPHABET;

    // All lowercase letters should return true
    for(char c = 'a'; c <= 'z'; c++) {
        EXPECT_TRUE(char_already_guessed(&state, c))
            << "Character '" << c << "' should be found";
    }

    // Uppercase letters should return false (case sensitive)
    EXPECT_FALSE(char_already_guessed(&state, 'A'));
    EXPECT_FALSE(char_already_guessed(&state, 'Z'));
}

TEST(HangmanLogicTest, CharAlreadyGuessedCaseSensitive) {
    GameState state;
    state.guessed[0] = 'a';
    state.guessed[1] = 'B';
    state.guess_count = 2;

    // Lowercase 'a' was guessed
    EXPECT_TRUE(char_already_guessed(&state, 'a'));
    EXPECT_FALSE(char_already_guessed(&state, 'A'));

    // Uppercase 'B' was guessed
    EXPECT_TRUE(char_already_guessed(&state, 'B'));
    EXPECT_FALSE(char_already_guessed(&state, 'b'));
}

TEST(HangmanLogicTest, CharAlreadyGuessedFirstAndLast) {
    GameState state;
    state.guessed[0] = 'a';
    state.guessed[1] = 'b';
    state.guessed[2] = 'c';
    state.guessed[3] = 'd';
    state.guessed[4] = 'z';
    state.guess_count = 5;

    // First guess
    EXPECT_TRUE(char_already_guessed(&state, 'a'));

    // Last guess
    EXPECT_TRUE(char_already_guessed(&state, 'z'));

    // Middle guesses
    EXPECT_TRUE(char_already_guessed(&state, 'b'));
    EXPECT_TRUE(char_already_guessed(&state, 'c'));
    EXPECT_TRUE(char_already_guessed(&state, 'd'));
}

// Test list_guessed_letters function
TEST(HangmanLogicTest, ListGuessedLettersEmpty) {
    GameState state;
    state.guess_count = 0;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "");
}

TEST(HangmanLogicTest, ListGuessedLettersSingle) {
    GameState state;
    state.guessed[0] = 'a';
    state.guess_count = 1;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "a");
}

TEST(HangmanLogicTest, ListGuessedLettersAlreadySorted) {
    GameState state;
    state.guessed[0] = 'a';
    state.guessed[1] = 'b';
    state.guessed[2] = 'c';
    state.guess_count = 3;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "a b c");
}

TEST(HangmanLogicTest, ListGuessedLettersNeedsSorting) {
    GameState state;
    state.guessed[0] = 'z';
    state.guessed[1] = 'a';
    state.guessed[2] = 'm';
    state.guessed[3] = 'c';
    state.guess_count = 4;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "a c m z");
}

TEST(HangmanLogicTest, ListGuessedLettersReverseSorted) {
    GameState state;
    state.guessed[0] = 'z';
    state.guessed[1] = 'y';
    state.guessed[2] = 'x';
    state.guessed[3] = 'w';
    state.guess_count = 4;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "w x y z");
}

TEST(HangmanLogicTest, ListGuessedLettersRandomOrder) {
    GameState state;
    state.guessed[0] = 'p';
    state.guessed[1] = 'y';
    state.guessed[2] = 't';
    state.guessed[3] = 'h';
    state.guessed[4] = 'o';
    state.guessed[5] = 'n';
    state.guess_count = 6;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "h n o p t y");
}

TEST(HangmanLogicTest, ListGuessedLettersFullAlphabet) {
    GameState state;
    // Fill with alphabet in reverse order
    for(int i = 0; i < NUM_ALPHABET; i++) {
        state.guessed[i] = 'z' - i;
    }
    state.guess_count = NUM_ALPHABET;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    // Should be sorted alphabetically with spaces
    EXPECT_STREQ(letters, "a b c d e f g h i j k l m n o p q r s t u v w x y z");
}

TEST(HangmanLogicTest, ListGuessedLettersDuplicatesNotExpected) {
    GameState state;
    // Test with what would be typical game play (no duplicates expected)
    state.guessed[0] = 'a';
    state.guessed[1] = 'e';
    state.guessed[2] = 'i';
    state.guessed[3] = 'o';
    state.guessed[4] = 'u';
    state.guess_count = 5;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    EXPECT_STREQ(letters, "a e i o u");
}

TEST(HangmanLogicTest, ListGuessedLettersMixedCase) {
    GameState state;
    state.guessed[0] = 'Z';
    state.guessed[1] = 'a';
    state.guessed[2] = 'B';
    state.guess_count = 3;
    char letters[NUM_ALPHABET * 2];

    int result = list_guessed_letters(&state, letters);

    EXPECT_EQ(result, 0);
    // Uppercase letters come before lowercase in ASCII
    EXPECT_STREQ(letters, "B Z a");
}

// Test all_guessed function
TEST(HangmanLogicTest, AllGuessedNoneGuessed) {
    GameState state;
    char secret[] = "cat";
    state.secret = secret;
    state.len_secret = strlen(secret);
    state.guess_count = 0;

    EXPECT_FALSE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedPartiallyGuessed) {
    GameState state;
    char secret[] = "cat";
    state.secret = secret;
    state.len_secret = strlen(secret);
    state.guessed[0] = 'c';
    state.guessed[1] = 'a';
    state.guess_count = 2;

    // Missing 't'
    EXPECT_FALSE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedCompletelyGuessed) {
    GameState state;
    char secret[] = "cat";
    state.secret = secret;
    state.len_secret = strlen(secret);
    state.guessed[0] = 'c';
    state.guessed[1] = 'a';
    state.guessed[2] = 't';
    state.guess_count = 3;

    EXPECT_TRUE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedExtraLettersGuessed) {
    GameState state;
    char secret[] = "cat";
    state.secret = secret;
    state.len_secret = strlen(secret);
    // Guessed more letters than needed
    state.guessed[0] = 'c';
    state.guessed[1] = 'a';
    state.guessed[2] = 't';
    state.guessed[3] = 'x';
    state.guessed[4] = 'y';
    state.guessed[5] = 'z';
    state.guess_count = 6;

    // All letters in secret are guessed (plus some wrong ones)
    EXPECT_TRUE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedSingleLetterWord) {
    GameState state;
    char secret[] = "a";
    state.secret = secret;
    state.len_secret = 1;
    state.guessed[0] = 'a';
    state.guess_count = 1;

    EXPECT_TRUE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedRepeatedLettersInWord) {
    GameState state;
    char secret[] = "letter";
    state.secret = secret;
    state.len_secret = strlen(secret);
    // Only need to guess each unique letter once
    state.guessed[0] = 'l';
    state.guessed[1] = 'e';
    state.guessed[2] = 't';
    state.guessed[3] = 'r';
    state.guess_count = 4;

    EXPECT_TRUE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedLongWord) {
    GameState state;
    char secret[] = "programming";
    state.secret = secret;
    state.len_secret = strlen(secret);
    // Guess all unique letters: p, r, o, g, a, m, i, n
    state.guessed[0] = 'p';
    state.guessed[1] = 'r';
    state.guessed[2] = 'o';
    state.guessed[3] = 'g';
    state.guessed[4] = 'a';
    state.guessed[5] = 'm';
    state.guessed[6] = 'i';
    state.guessed[7] = 'n';
    state.guess_count = 8;

    EXPECT_TRUE(all_guessed(&state));
}

TEST(HangmanLogicTest, AllGuessedMissingOneLetterInLongWord) {
    GameState state;
    char secret[] = "programming";
    state.secret = secret;
    state.len_secret = strlen(secret);
    // Missing 'n'
    state.guessed[0] = 'p';
    state.guessed[1] = 'r';
    state.guessed[2] = 'o';
    state.guessed[3] = 'g';
    state.guessed[4] = 'a';
    state.guessed[5] = 'm';
    state.guessed[6] = 'i';
    state.guess_count = 7;

    EXPECT_FALSE(all_guessed(&state));
}

// Test game_lost function
TEST(HangmanLogicTest, GameLostNoWrongGuesses) {
    GameState state;
    state.wrong_count = 0;

    EXPECT_FALSE(game_lost(&state));
}

TEST(HangmanLogicTest, GameLostSomeWrongGuesses) {
    GameState state;
    state.wrong_count = 3;

    EXPECT_FALSE(game_lost(&state));
}

TEST(HangmanLogicTest, GameLostAtLimit) {
    GameState state;
    state.wrong_count = NUM_PICS;

    // At the limit, not lost yet
    EXPECT_FALSE(game_lost(&state));
}

TEST(HangmanLogicTest, GameLostExceedsLimit) {
    GameState state;
    state.wrong_count = NUM_PICS + 1;

    EXPECT_TRUE(game_lost(&state));
}

TEST(HangmanLogicTest, GameLostMaxWrongGuesses) {
    GameState state;
    state.wrong_count = NUM_PICS + 10;

    EXPECT_TRUE(game_lost(&state));
}

TEST(HangmanLogicTest, GameLostBoundaryCheck) {
    GameState state;

    // Just below the limit
    state.wrong_count = NUM_PICS - 1;
    EXPECT_FALSE(game_lost(&state));

    // At the limit
    state.wrong_count = NUM_PICS;
    EXPECT_FALSE(game_lost(&state));

    // Just over the limit
    state.wrong_count = NUM_PICS + 1;
    EXPECT_TRUE(game_lost(&state));
}
