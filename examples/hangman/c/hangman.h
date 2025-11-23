#ifndef __HANGMAN_H
#define __HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LEN  50
#define MAX_HINT_LEN  100
#define NUM_WORDS     10    // This will grow with bigger dictionary

#define NUM_ALPHABET  26

typedef struct {
	char word[MAX_WORD_LEN];
	char hint[MAX_HINT_LEN];
} WordHint;    // Word and Hint

typedef struct {
	char  *secret;
	int    len_secret;
	char   guessed[NUM_ALPHABET];
	int    guess_count;
	int    wrong_count;

} GameState;

extern WordHint words[NUM_WORDS];
extern const int NUM_PICS;

#ifdef __cplusplus
extern "C" {
#endif

	// Hangman Functions
	int choose_word(WordHint *selected);
	void display_game_state(GameState *state);
	bool char_in_secret(GameState *state, char check);
	bool char_already_guessed(GameState *state, char check);
	int list_guessed_letters(GameState *state, char *letters);
	bool all_guessed(GameState *state);	
	bool game_lost(GameState *state);


#ifdef __cplusplus
}
#endif

#endif // __HANGMAN_H
