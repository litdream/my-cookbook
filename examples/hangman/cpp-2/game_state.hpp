#ifndef __GAME_STATE_HPP
#define __GAME_STATE_HPP

#include <random>
#include <string>
#include <vector>

using std::string;
using std::vector;

enum ProcessResult { SUCCESS, DUP_GUESS, NOT_ALPHA };

struct WordHint {
    string word;
    string hint;
};

class GameState {
public:
    GameState();
    GameState(const string &secret, const string &hint);
    bool GameOver();
    bool DidWin();
    void DrawScreen();
    ProcessResult ProcessGuess(char guess);
    string GetSecret();

private:
    string secret;
    string hint;
    std::vector<char> guessed;
    int wrong_count;
    std::mt19937 rng;
};

#endif // __GAME_STATE_HPP
