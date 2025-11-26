#include "game_state.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>

using std::cout;
using std::string;
using std::vector;

const int NUM_PICS = 7;
const std::array<const char *, NUM_PICS> hangman_pics = {
    R"(
     +---+
         |
         |
         |
       ===)",

    R"(
     +---+
     O   |
         |
         |
       ===)",

    R"(
     +---+
     O   |
     |   |
         |
       ===)",

    R"(
     +---+
     O   |
    /|   |
         |
       ===)",

    R"(
     +---+
     O   |
    /|\  |
         |
       ===)",

    R"(
     +---+
     O   |
    /|\  |
    /    |
       ===)",

    R"(
     +---+
     O   |
    /|\  |
    / \  |
       ===)"};

const int NUM_WORDS = 10;
WordHint words[NUM_WORDS] = {
    {"python", "A programming language known for its readability."},
    {"gravity", "A natural force that pulls objects toward each other."},
    {"castle", "A large fortified building from medieval times."},
    {"keyboard", "A device with keys used to type."},
    {"forest", "A large area covered mostly with trees."},
    {"planet", "A celestial body orbiting a star."},
    {"battery", "A portable power source."},
    {"mountain", "A large natural elevation of the Earth's surface."},
    {"library", "A place where books are kept."},
    {"rhythm", "A repeated pattern of movement or sound."}};

GameState::GameState() : wrong_count(0), rng(std::random_device{}()) {
    int idx = rng() % NUM_WORDS;
    secret = (words[idx].word);
    hint = (words[idx].hint);
}

GameState::GameState(const string &secret, const string &hint)
    : secret(secret), hint(hint), wrong_count(0) {}


bool GameState::GameOver() {
    return DidWin() || (wrong_count >= NUM_PICS);
}

bool GameState::DidWin() {
    for (char c : secret) {
        if (std::find(guessed.begin(), guessed.end(), c) == guessed.end()) {
            return false;
        }
    }
    return true;
}

void GameState::DrawScreen() {
    cout << "\n" << hangman_pics[wrong_count] << "\n";
    cout << "\n";

    // Current matching status
    cout << "Word: ";
    for (char c : secret) {
        if (std::find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }

    // Guessed letters.  
    cout << "\nGuessed letters: ";
    for (char c : guessed) {
        cout << c << " ";
    }
    cout << "\n\n";
}

ProcessResult GameState::ProcessGuess(char guess) {
    // alphabet check.
    if (!std::isalpha(guess)) {
        return NOT_ALPHA;
    }

    guess = std::tolower(guess);

    // duplicate check
    if (std::find(guessed.begin(), guessed.end(), guess) != guessed.end()) {
        return DUP_GUESS;
    }

    // append to guessed
    guessed.push_back(guess);
    std::sort(guessed.begin(), guessed.end());

    // determine:  current char is in secret.
    if (secret.find(guess) == std::string::npos) {
        wrong_count++;
    }

    return SUCCESS;
}

std::string GameState::GetSecret() { return secret; }
