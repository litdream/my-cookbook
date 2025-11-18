#include "bullgame.hpp"


BullCowGame::BullCowGame(int maxTry) {
    com.clear();
    com.resize(DIGITS);

    // Generate Random number:  Borrowed from Claude:
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 9);

    do {
        for (int i=0; i<DIGITS; ++i) {
            com[i] = dist(gen);
        }
    } while ( com[0] == com[1] ||
              com[0] == com[2] ||
              com[1] == com[2] );
}

Result
BullCowGame::match(const string& guess) const {
    Result result;
    vector<int> userGuess(DIGITS);

    for (int i=0; i<DIGITS; ++i) {
        userGuess[i] = guess[i] - '0';
    }

    // count bulls
    for (int i=0; i<DIGITS; ++i) {
        if (userGuess[i] == com[i])
            result.bulls++;
    }

    // count cows
    for (int i=0; i<DIGITS; ++i) {
        if (userGuess[i] == com[ (i+1) % DIGITS ] ||
            userGuess[i] == com[ (i+2) % DIGITS ] ) {
            result.cows++;
        }
    }

    return result;
}

string
BullCowGame::getComNum() const {
    string result;
    for (int digit : com) {
        result += std::to_string(digit);
    }
    return result;
    //  NOTE:  returning local variable by value,
    //         compiler is smart to use move-semantics:
    //         std::move(result);
}
