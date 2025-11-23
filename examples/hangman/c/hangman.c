#include "hangman.h"

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
    {"rhythm", "A repeated pattern of movement or sound."}
};

// Hangman drawings
const char *hangman_pics[] = {
    "\n"
    "     +---+\n"
    "         |\n"
    "         |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "         |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "     |   |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|   |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|\\  |\n"
    "         |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|\\  |\n"
    "    /    |\n"
    "       ===",

    "\n"
    "     +---+\n"
    "     O   |\n"
    "    /|\\  |\n"
    "    / \\  |\n"
    "       ==="
};
