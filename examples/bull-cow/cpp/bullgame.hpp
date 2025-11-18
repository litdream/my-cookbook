#ifndef BULLGAME_HPP
#define BULLGAME_HPP

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>

using std::vector;
using std::string;

static const int DIGITS = 3;

struct Result {
    int bulls;
    int cows;

    Result() : bulls(0), cows(0) {}
};

class BullCowGame {
public:
    BullCowGame(int maxTry=10);
    Result match(const string& guess) const;
    string getComNum() const;
private:
    vector<int> com;
};

#endif // BULLGAME_HPP
