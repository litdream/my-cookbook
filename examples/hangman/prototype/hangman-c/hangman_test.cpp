#include <gtest/gtest.h>
#include <cstring>
#include "hangman.h"

// Test the logic for checking if a letter exists in the array
TEST(HangmanLogicTest, IsLetterGuessed) {
    char guessed[] = {'a', 'z', 'q'};
    int count = 3;

    // Positive cases
    EXPECT_TRUE(is_letter_guessed(guessed, count, 'a'));
    EXPECT_TRUE(is_letter_guessed(guessed, count, 'z'));

    // Negative cases
    EXPECT_FALSE(is_letter_guessed(guessed, count, 'b'));
    EXPECT_FALSE(is_letter_guessed(guessed, count, ' '));
}

// Test the Win Condition logic
TEST(HangmanLogicTest, IsWordComplete) {
    const char* target = "hello";
    
    // Case 1: Incomplete word
    char partial_guess[] = {'h', 'e', 'l'}; // missing 'o'
    EXPECT_FALSE(is_word_complete(target, partial_guess, 3));

    // Case 2: Complete word (order shouldn't matter)
    char full_guess[] = {'o', 'l', 'e', 'h'};
    EXPECT_TRUE(is_word_complete(target, full_guess, 4));

    // Case 3: Complete word with extra garbage guesses
    char messy_guess[] = {'x', 'o', 'z', 'l', 'e', 'h'};
    EXPECT_TRUE(is_word_complete(target, messy_guess, 6));
}

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

// Test Display Logic (Sorting)
// Since display_state prints to stdout, we use GTest's capture feature
TEST(HangmanDisplayTest, SortsGuessedLetters) {
    const char* word = "cat";
    // Guessed: c, a, z, b (unsorted)
    char guessed[] = {'c', 'a', 'z', 'b'}; 
    
    testing::internal::CaptureStdout();
    display_state(word, guessed, 4, 0);
    std::string output = testing::internal::GetCapturedStdout();

    // The function prints guessed letters at the end.
    // We expect them to be printed as: a b c z
    // Note: your code prints them with spaces, e.g., "a b c z "
    
    EXPECT_TRUE(output.find("a b c z") != std::string::npos) 
        << "Output did not contain sorted letters. Got:\n" << output;
}

// Test Display Logic (Masking)
TEST(HangmanDisplayTest, MasksHiddenLetters) {
    const char* word = "apple";
    char guessed[] = {'p', 'e'}; // Missing 'a', 'l'
    
    testing::internal::CaptureStdout();
    display_state(word, guessed, 2, 0);
    std::string output = testing::internal::GetCapturedStdout();

    // Expect: _ p p _ e
    EXPECT_TRUE(output.find("_ p p _ e") != std::string::npos)
        << "Output didn't mask correctly. Got:\n" << output;
}
