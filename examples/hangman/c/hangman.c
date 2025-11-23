#include "hangman.h"

WordHint words[NUM_WORDS] = {
    {"python", "A programming language known for its readability."},
    {"gravity", "A natural force that pulls objects toward each other."},
    {"castle", "A large fortified building from medieval times."},
    {"keyboard", "A device with keys used to type."},
    {"forest", "A large area covered mostly with trees."},
    {"planet", "A celestial body orbiting a star."},
    {"battery", "A portable power source."},
    {"mountain", "A large natural elevation of the Earth's surface."},
    {"library", "A place where books are kept."},
    {"rhythm", "A repeated pattern of movement or sound."}
};

// Hangman drawings
const int NUM_PICS = 7;
const char *hangman_pics[] = {
    "\n"
    "     +---+\n"
    "         |\n"
    "         |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "         |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "     |   |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|   |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|\\  |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|\\  |\n"
    "    /    |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|\\  |\n"
    "    / \\  |\n"
    "       ==="
};


int choose_word(WordHint *selected) {
	int index = rand() % NUM_WORDS;
	*selected = words[index];
	return 0;
}

void display_game_state(GameState *state) {
	printf("\n%s\n", hangman_pics[ state->wrong_count ]);
	printf("\n");

	// secret status
	printf("Word: ");
	char *secret = state->secret;
	for (int i=0; i< state->len_secret; ++i) {
		if ( char_already_guessed(state, secret[i])) {
			printf(" %c", secret[i]);
		} else {
			printf(" _");
		}
	}

	// guessed letters
	//    - letters[] buffer holds ready-to-print texts.
	//      Which includes ' ' for spacing.  So, size is 2x of
	//      actual buffer size.
	char letters[ NUM_ALPHABET * 2 ];
	list_guessed_letters(state, letters);
	printf("\nGuessed letters: %s\n\n", letters);
}

// Parameter:
//   - state:   GameState, as usual
//   - letters: (buf: allocated from callee),
//              directly printable for convenience.
// Returns:  0 for success,
//           non-zero for reserve
//
int list_guessed_letters(GameState *state, char *letters) {
	char sorted[NUM_ALPHABET];
	memset(sorted, '\0', NUM_ALPHABET);

	// Copy guessed letters to sorted array
	memcpy(sorted, state->guessed, state->guess_count);

	// Bubble Sort.
	//   - Consider: For efficient Set() operation,
	//          BST might fit better.
	//   - For now, lazy method.
	for (int i = 0; i < state->guess_count - 1; ++i) {
		for (int j = 0; j < state->guess_count - i - 1; ++j) {
			if (sorted[j] > sorted[j + 1]) {
				char temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
		}
	}

	// Build output string with spaces between letters
	int pos = 0;
	for (int i = 0; i < state->guess_count; ++i) {
		if (i > 0) {
			letters[pos++] = ' ';
		}
		letters[pos++] = sorted[i];
	}
	letters[pos] = '\0';  // Null-terminate the string

	return 0;
}

bool char_in_secret(GameState *state, char chk) {
	char *secret = state->secret;
	for (int i=0; i< state->len_secret; ++i)
		if (secret[i] == chk)
			return true;
	return false;
}

bool char_already_guessed(GameState *state, char chk) {
	char *guessed = state->guessed;
	for (int i=0; i< state->guess_count; ++i)
		if (guessed[i] == chk)
			return true;
	return false;
}

bool all_guessed(GameState *state) {
	char *secret = state->secret;
	for (int i=0; i< state->len_secret; ++i) 
		if ( ! char_already_guessed(state, secret[i]))
			return false;
	return true;
}

bool game_lost(GameState *state) {
	return state->wrong_count >= NUM_PICS;
}
