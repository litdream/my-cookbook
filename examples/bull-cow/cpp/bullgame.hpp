#ifndef BULLGAME_HPP
#define BULLGAME_HPP

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>

static const int DIGITS = 3;

struct Result {
    int bulls;
    int cows;

    Result() : bulls(0), cows(0) {}
};

class BullCowGame {
public:
    BullCowGame(int maxTry=10);
    Result match(const std::string& guess) const;
    std::string getComNum() const;
private:
    std::vector<int> com;
};

#endif // BULLGAME_HPP
