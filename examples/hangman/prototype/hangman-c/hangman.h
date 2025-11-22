#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdbool.h>

#define MAX_WORD_LEN 50
#define MAX_HINT_LEN 100
#define MAX_GUESSES 26
#define NUM_WORDS 10

typedef struct {
    char word[MAX_WORD_LEN];
    char hint[MAX_HINT_LEN];
} WordHint;

// Expose definitions for testing
extern WordHint words[NUM_WORDS];

// Function Prototypes
// Wrapped in extern "C" so C++ Test files can link to them correctly
#ifdef __cplusplus
extern "C" {
#endif

int choose_word(WordHint *selected);
void display_state(const char *word, const char *guessed_letters, int num_guessed, int wrong_guesses);
bool is_letter_guessed(const char *guessed_letters, int num_guessed, char letter);
bool is_word_complete(const char *word, const char *guessed_letters, int num_guessed);
void hangman();

#ifdef __cplusplus
}
#endif

#endif // HANGMAN_H
