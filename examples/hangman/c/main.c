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
	char input[100];

	printf(" == HANGMAN Game ==\n");

	// Init Game State
	srand(time(NULL));
	WordHint selected;

	if ( choose_word(&selected) != 0 ) {
		perror("word selection failed.");
		return 1;
	}

	// Random Word guess


	while (true) {
		// Print state



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





		// DEBUG: Echo
		printf("your word: [%s]\n", input);
	}

	return 0;
}
