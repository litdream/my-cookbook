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

typedef struct {
	char word[MAX_WORD_LEN];
	char hint[MAX_HINT_LEN];
} WordHint;    // Word and Hint

extern WordHint words[NUM_WORDS];  

#ifdef __cplusplus
extern "C" {
#endif

// Hangman Functions
	


#ifdef __cplusplus
}
#endif
	
#endif // __HANGMAN_H
