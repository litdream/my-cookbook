#include <iostream>
#include "game_state.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main() {
	GameState game;

	while ( ! game.GameOver()) {
		game.DrawScreen();


		// TODO:  Make it better
		// - Lazy impl:  Multiple chars will mess this.
		//
		char guess;
		cout << "\nGuess a letter: ";
		cin >> guess;
		if ( ! cin.good()) {
			cout << "End of input detected.  Exiting.\n";
			break;
		}

		switch ( game.ProcessGuess(guess)) {
		SUCCESS:
			break;

		DUP_GUESS:
			cout << "char(" << guess << ") was previously guessed already.\n";
			break;
		NOT_ALPHA:
			cout << "only provide alphabet.\n";
			break;
		default:
			cout << "UNLIKELY\n";	
		}
	}

	if ( game.DidWin()) 
		cout << "Congratulations!  That was it: ";
	else 
		cout << "Sorry..  The word was: ";
	cout << game.GetSecret() << endl;

	return 0;	
}
