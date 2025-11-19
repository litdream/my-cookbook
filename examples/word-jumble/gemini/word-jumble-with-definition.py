#!/usr/bin/env python3
import random
import sys

# Word → definition
WORD_DEFS = {
    "python": "A popular programming language known for readability.",
    "variable": "A named place in memory that stores a value.",
    "function": "A reusable block of code that performs an action.",
    "object": "An instance of a class in object-oriented programming.",
    "syntax": "The rules defining how code must be written.",
    "orange": "A citrus fruit known for its bright color and vitamin C.",
    "silver": "A precious metal with atomic number 47.",
    "planet": "A celestial body orbiting a star.",
    "gravity": "A natural force that attracts bodies toward one another.",
    "rhythm": "A strong, repeated pattern of movement or sound.",
    "window": "An opening in a wall to let in light or air.",
    "library": "A collection of books or a place to borrow them.",
    "keyboard": "A device with keys used to input text into a computer.",
    "monitor": "A screen that displays output from a computer.",
    "battery": "A device that stores energy and powers electronics.",
    "castle": "A fortified building from medieval times.",
    "forest": "A large area covered chiefly with trees and undergrowth.",
    "dragon": "A mythical creature that breathes fire in many stories.",
    "mountain": "A large natural elevation of Earth's surface.",
    "river": "A natural flowing watercourse that usually flows into a sea."
}

WORD_LIST = list(WORD_DEFS.keys())


def jumble_word(word: str) -> str:
    letters = list(word)
    while True:
        random.shuffle(letters)
        scrambled = ''.join(letters)
        if scrambled != word:
            return scrambled


def play_round(word):
    scrambled = jumble_word(word)
    attempts = 0
    hint_used = False

    print(f"\nScrambled word: {scrambled}")
    print(f"Definition: {WORD_DEFS[word]}")
    print("Type your guess, 'hint' for the first letter, or 'quit' to exit.")

    while True:
        guess = input("Your guess: ").strip().lower()
        attempts += 1

        if guess == "quit":
            print("Goodbye!")
            sys.exit(0)

        if guess == "hint":
            if not hint_used:
                print(f"Hint: The word starts with '{word[0]}'")
                hint_used = True
            else:
                print("You already used your hint.")
            continue

        if guess == word:
            print(f"Correct! The word was '{word}'.")
            return attempts, hint_used
        else:
            print("Nope, try again.")


def main():
    print("=== WORD JUMBLE WITH DEFINITIONS ===")
    print("Unscramble the word using its definition! Type 'quit' to exit.\n")

    score = 0

    while True:
        word = random.choice(WORD_LIST)
        attempts, hint_used = play_round(word)

        # simple scoring system
        points = max(10 - attempts, 1)
        if hint_used:
            points -= 2
        if points < 1:
            points = 1

        score += points
        print(f"You earned {points} points. Total score: {score}\n")

        again = input("Play again? [y/n] ").strip().lower()
        if again != "y":
            break

    print("\nThanks for playing!")
    print(f"Final score: {score}")


if __name__ == "__main__":
    main()

