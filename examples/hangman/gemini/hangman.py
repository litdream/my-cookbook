#!/usr/bin/env python3
import random
import sys

# Words + definitions (optional hint)
WORDS = {
    "python": "A programming language known for its readability.",
    "gravity": "A natural force that pulls objects toward each other.",
    "castle": "A large fortified building from medieval times.",
    "keyboard": "A device with keys used to type.",
    "forest": "A large area covered mostly with trees.",
    "planet": "A celestial body orbiting a star.",
    "battery": "A portable power source.",
    "mountain": "A large natural elevation of the Earth's surface.",
    "library": "A place where books are kept.",
    "rhythm": "A repeated pattern of movement or sound."
}

# Hangman drawings
HANGMAN_PICS = [
    """
     +---+
         |
         |
         |
       ===""",
    """
     +---+
     O   |
         |
         |
       ===""",
    """
     +---+
     O   |
     |   |
         |
       ===""",
    """
     +---+
     O   |
    /|   |
         |
       ===""",
    """
     +---+
     O   |
    /|\\  |
         |
       ===""",
    """
     +---+
     O   |
    /|\\  |
    /    |
       ===""",
    """
     +---+
     O   |
    /|\\  |
    / \\  |
       ==="""
]


def choose_word():
    return random.choice(list(WORDS.keys()))


def display_state(word, guessed_letters, wrong_guesses):
    print(HANGMAN_PICS[wrong_guesses])
    print("\nWord: ", end="")
    revealed = [letter if letter in guessed_letters else "_" for letter in word]
    print(" ".join(revealed))
    print("Guessed letters: ", " ".join(sorted(guessed_letters)))
    print()


def hangman():
    print("=== HANGMAN ===")
    print("Guess the word one letter at a time.")
    print("Type 'hint' for a definition, 'quit' to exit.\n")

    word = choose_word()
    guessed_letters = set()
    wrong_guesses = 0
    max_wrong = len(HANGMAN_PICS) - 1
    hint_used = False

    while True:
        display_state(word, guessed_letters, wrong_guesses)

        guess = input("Your guess: ").strip().lower()

        if guess == "quit":
            print("Goodbye!")
            sys.exit(0)

        if guess == "hint":
            if not hint_used:
                print("Hint:", WORDS[word])
                hint_used = True
            else:
                print("You already used your hint.")
            continue

        if len(guess) != 1 or not guess.isalpha():
            print("Please enter a single letter.")
            continue

        if guess in guessed_letters:
            print("You already guessed that letter.")
            continue

        guessed_letters.add(guess)

        if guess not in word:
            print("Wrong!")
            wrong_guesses += 1

        # Check loss
        if wrong_guesses >= max_wrong:
            display_state(word, guessed_letters, wrong_guesses)
            print("You lost! The word was:", word)
            break

        # Check win
        if all(letter in guessed_letters for letter in word):
            display_state(word, guessed_letters, wrong_guesses)
            print("You won! The word was:", word)
            break


if __name__ == "__main__":
    try:
        hangman()
    except KeyboardInterrupt:
        print("\nExiting…")
        sys.exit(0)

