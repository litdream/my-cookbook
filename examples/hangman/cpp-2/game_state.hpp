#ifndef __GAME_STATE_HPP
#define __GAME_STATE_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

enum ProcessResult {
	SUCCESS,
	DUP_GUESS,
	NOT_ALPHA
};

class GameState {
public:
	GameState();
	bool GameOver();
	bool DidWin();
	void DrawScreen();
	ProcessResult  ProcessGuess(char guess);
	string  GetSecret();

private:
	string  secret;
	vector<char>  guessed;	
	int  wrong_count;
};


#endif   // __GAME_STATE_HPP
