/**  Good Sample Output:  from Gemini's prototype
 *

=== HANGMAN ===
Guess the word one letter at a time.
Type 'hint' for a definition, 'quit' to exit.


     +---+
         |
         |
         |
       ===

Word: _ _ _ _ _ _
Guessed letters:

Your guess:


**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>   // To use true/false keyword-like
#include "hangman.h"

int main() {
	printf(" == HANGMAN Game ==\n");

	// Init Game State
	char input[100];
	WordHint selected;
	GameState  gamestate;

	memset(&gamestate,  '\0', sizeof(GameState));
	srand(time(NULL));
	if ( choose_word(&selected) != 0 ) {
		perror("word selection failed.");
		return 1;
	}
	gamestate.secret = selected.word;
	gamestate.len_secret = strlen(gamestate.secret);

	while (true) {
		// Print state
		display_game_state(&gamestate);

		printf("Your guess: ");
		if (fgets(input, sizeof(input), stdin) == NULL) {
			// If Ctrl-D, break and finish the game.
			break;
		}

		// chop the '\n':  It's guranteed by fgets()
		char *newline = strchr(input, '\n');
		if (newline != NULL) {
			*newline = '\0';
		}

		// Because I did not trim the front part,
		// assuring length-1-string is useful.
		if ( strnlen(input, NUM_ALPHABET) > 1) {
			printf("I said: SINGLE CHAR!!\n");
			continue;
		}
		if ( char_already_guessed(&gamestate, input[0])) {
			printf("Char(%c) is already guessed. Try again.\n", input[0]);
			continue;
		}
		gamestate.guessed[ gamestate.guess_count++ ] = input[0];

		if ( ! char_in_secret(&gamestate, input[0]))
			gamestate.wrong_count++;

		// Win State:
		if ( all_guessed(&gamestate)) {
			printf("Congratulations!  You won.\n");
			return 0;
		}

		// Lose State:
		if ( game_lost(&gamestate)) {
			printf("Sorry.  The word was: %s\n", gamestate.secret);
			return 0;
		}
	}

	return 0;
}
