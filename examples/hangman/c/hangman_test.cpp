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
