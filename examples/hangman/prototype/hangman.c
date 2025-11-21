#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAX_WORD_LEN 50
#define MAX_HINT_LEN 100
#define MAX_GUESSES 26
#define NUM_WORDS 10

typedef struct {
    char word[MAX_WORD_LEN];
    char hint[MAX_HINT_LEN];
} WordHint;

// Words + definitions (optional hint)
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

#define MAX_WRONG 6

int choose_word(WordHint *selected) {
    int index = rand() % NUM_WORDS;
    *selected = words[index];
    return 0;
}

void display_state(const char *word, const char *guessed_letters, int num_guessed, int wrong_guesses) {
    printf("%s\n", hangman_pics[wrong_guesses]);
    printf("\nWord: ");

    for (int i = 0; word[i] != '\0'; i++) {
        bool found = false;
        for (int j = 0; j < num_guessed; j++) {
            if (guessed_letters[j] == word[i]) {
                found = true;
                break;
            }
        }
        if (found) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }

    printf("\nGuessed letters: ");
    // Sort and display guessed letters
    char sorted[MAX_GUESSES];
    memcpy(sorted, guessed_letters, num_guessed);
    sorted[num_guessed] = '\0';

    // Simple bubble sort
    for (int i = 0; i < num_guessed - 1; i++) {
        for (int j = 0; j < num_guessed - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                char temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < num_guessed; i++) {
        printf("%c ", sorted[i]);
    }
    printf("\n\n");
}

bool is_letter_guessed(const char *guessed_letters, int num_guessed, char letter) {
    for (int i = 0; i < num_guessed; i++) {
        if (guessed_letters[i] == letter) {
            return true;
        }
    }
    return false;
}

bool is_word_complete(const char *word, const char *guessed_letters, int num_guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!is_letter_guessed(guessed_letters, num_guessed, word[i])) {
            return false;
        }
    }
    return true;
}

void hangman() {
    printf("=== HANGMAN ===\n");
    printf("Guess the word one letter at a time.\n");
    printf("Type 'hint' for a definition, 'quit' to exit.\n\n");

    WordHint selected;
    choose_word(&selected);

    char guessed_letters[MAX_GUESSES];
    int num_guessed = 0;
    int wrong_guesses = 0;
    bool hint_used = false;
    char input[100];

    while (true) {
        display_state(selected.word, guessed_letters, num_guessed, wrong_guesses);

        printf("Your guess: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        // Convert to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        // Trim whitespace
        char *guess = input;
        while (isspace(*guess)) guess++;
        char *end = guess + strlen(guess) - 1;
        while (end > guess && isspace(*end)) end--;
        *(end + 1) = '\0';

        if (strcmp(guess, "quit") == 0) {
            printf("Goodbye!\n");
            exit(0);
        }

        if (strcmp(guess, "hint") == 0) {
            if (!hint_used) {
                printf("Hint: %s\n", selected.hint);
                hint_used = true;
            } else {
                printf("You already used your hint.\n");
            }
            continue;
        }

        if (strlen(guess) != 1 || !isalpha(guess[0])) {
            printf("Please enter a single letter.\n");
            continue;
        }

        char letter = guess[0];

        if (is_letter_guessed(guessed_letters, num_guessed, letter)) {
            printf("You already guessed that letter.\n");
            continue;
        }

        guessed_letters[num_guessed++] = letter;

        // Check if letter is in word
        bool found = false;
        for (int i = 0; selected.word[i] != '\0'; i++) {
            if (selected.word[i] == letter) {
                found = true;
                break;
            }
        }

        if (!found) {
            printf("Wrong!\n");
            wrong_guesses++;
        }

        // Check loss
        if (wrong_guesses >= MAX_WRONG) {
            display_state(selected.word, guessed_letters, num_guessed, wrong_guesses);
            printf("You lost! The word was: %s\n", selected.word);
            break;
        }

        // Check win
        if (is_word_complete(selected.word, guessed_letters, num_guessed)) {
            display_state(selected.word, guessed_letters, num_guessed, wrong_guesses);
            printf("You won! The word was: %s\n", selected.word);
            break;
        }
    }
}

int main(void) {
    // Seed random number generator
    srand(time(NULL));

    hangman();

    return 0;
}
