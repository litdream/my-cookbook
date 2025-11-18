// g++ -std=c++14 -c bullgame.cpp
// g++ -std=c++14 main.cpp bullgame.o
// 
#include <iostream>
#include <string>
#include "bullgame.hpp"

using std::cin;
using std::cout;
using std::cerr;
using std::string;
using std::endl;

// 11/17 Journal study doc:
void _rtrim(string &s) {
    auto it = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    });
    s.erase(it.base(), s.end());
}

int main() {
    BullCowGame game(10);
    string userinput;
    int round =1;
    
    cout << "Welcome to The Bulls/Cows number guessing game.\n";
    while (round <= 10) {
        cout << "Round " << round
             << ": Enter your 3-digit guess (e.g., 123): ";
        cin >> userinput;
        _rtrim(userinput);
        
        // TODO: validate userinput

        Result res = game.match(userinput);
        if (res.bulls == 3) {
            cout << "Great! You got this in %d rounds. The number was: "
                 << game.getComNum() << endl;
            return 0;
        }
        cout << res.bulls << " bulls, " << res.cows << " cows\n";
        ++round;
    }

    cout << "Sorry.  The number was " << game.getComNum() << std::endl;
    
    return 0;
}
