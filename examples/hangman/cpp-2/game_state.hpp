#ifndef __GAME_STATE_HPP
#define __GAME_STATE_HPP

#include <random>
#include <string>
#include <vector>

enum ProcessResult { SUCCESS, DUP_GUESS, NOT_ALPHA };

struct WordHint {
    std::string word;
    std::string hint;
};

class GameState {
public:
    GameState();
    GameState(const std::string &secret, const std::string &hint);
    bool GameOver();
    bool DidWin();
    void DrawScreen();
    ProcessResult ProcessGuess(char guess);
    std::string GetSecret();

private:
    std::string secret;
    std::string hint;
    std::vector<char> guessed;
    int wrong_count;
    std::mt19937 rng;
};

#endif // __GAME_STATE_HPP
