#include <iostream>
#include "game_state.hpp"

#include <cstdio>

using std::cout;


GameState::GameState() {}

bool
GameState::GameOver() {
	// TODO: implement
	return false;

}

bool
GameState::DidWin() {
	// TODO: implement
	return true;
}

void 
GameState::DrawScreen() {
	// TODO: implement
	cout << "GAME: \n";	
}

ProcessResult
GameState::ProcessGuess(char guess) {
	// TODO: implement
	printf("got: %c(%d)\n", guess, guess);	
	return SUCCESS;
}

std::string
GameState::GetSecret() {
	return secret;
}
