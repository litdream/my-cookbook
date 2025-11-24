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


#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "hangman.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main() {
    printf(" == HANGMAN Game ==\n");

    // Init Game State
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

        std::string input;
        cout << "Your guess: ";
        std::getline(cin, input);

        if (input.length() > 1) {
            cout << "I said: SINGLE CHAR!!\n";
            continue;
        }
        if ( char_already_guessed(&gamestate, input[0])) {
            cout << "Char(" << input[0] << ") is already guessed. Try again.\n";
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
