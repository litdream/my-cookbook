#include "game_state.hpp"

#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main() {
    GameState game;

    while (!game.GameOver()) {
        cout << "\n -------------------- \n";
        game.DrawScreen();

        // TODO:  Make it better
        // - Lazy impl:  Multiple chars will mess this.
        // ´
        char guess;
        cout << "\nGuess a letter: ";
        cin >> guess;

        // detect Ctrl-D:
        if (!cin.good()) {
            cout << "End of input detected.  Exiting.\n";
            break;
        }

        switch (game.ProcessGuess(guess)) {
        case SUCCESS:
            break;

        case DUP_GUESS:
            cout << "char(" << guess << ") was previously guessed already.\n";
            break;
        case NOT_ALPHA:
            cout << "only provide alphabet.\n";
            break;
        default:
            cout << "UNLIKELY\n";
        }
    }

    if (game.DidWin())
        cout << "Congratulations!  That was it: ";
    else
        cout << "Sorry..  The word was: ";
    cout << game.GetSecret() << endl;

    return 0;
}
