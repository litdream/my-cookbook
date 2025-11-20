#!/usr/bin/env python3
import random
import sys

# You can expand this list or load from a file
WORD_LIST = [
    "python", "variable", "function", "object", "syntax",
    "orange", "silver", "planet", "gravity", "rhythm",
    "window", "library", "keyboard", "monitor", "battery",
    "castle", "forest", "dragon", "mountain", "river"
]


def jumble_word(word: str) -> str:
    """Return a scrambled version of the word."""
    letters = list(word)
    # To avoid cases where shuffle returns original order
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
    print("Type your guess, 'hint' for a hint, or 'quit' to exit.")

    while True:
        guess = input("Your guess: ").strip().lower()
        attempts += 1

        if guess == "quit":
            print("Goodbye!")
            sys.exit(0)

        if guess == "hint":
            if not hint_used:
                print(f"Hint: The first letter is '{word[0]}'")
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
    print("=== WORD JUMBLE GAME ===")
    print("Unscramble the word! Type 'quit' to exit.\n")

    score = 0
    round_num = 0

    while True:
        round_num += 1
        word = random.choice(WORD_LIST)
        attempts, hint_used = play_round(word)

        # Scoring
        points = max(10 - attempts, 1)
        if hint_used:
            points -= 2
        if points < 1:
            points = 1

        score += points
        print(f"You earned {points} points. Total score: {score}\n")

        # Continue?
        again = input("Play again? [y/n] ").strip().lower()
        if again != 'y':
            break

    print("\nThanks for playing Word Jumble!")
    print(f"Final score: {score}")
    print("Goodbye!")


if __name__ == "__main__":
    main()

