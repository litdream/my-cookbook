#!/usr/bin/env python3
import random
import sys

# Words grouped by category
CATEGORIES = {
    "animals": {
        "elephant": "A large mammal with a trunk.",
        "giraffe": "A tall African mammal with a very long neck.",
        "dolphin": "A highly intelligent marine mammal.",
        "penguin": "A flightless bird that lives in cold regions.",
        "kangaroo": "A jumping marsupial from Australia."
    },
    "technology": {
        "python": "A programming language known for readability.",
        "keyboard": "A device used to type input into computers.",
        "battery": "A portable device that stores energy.",
        "monitor": "A display screen used with computers.",
        "router": "A device that forwards data packets on a network."
    },
    "geography": {
        "planet": "A celestial body orbiting a star.",
        "mountain": "A large natural elevation of Earth's surface.",
        "desert": "A dry, barren region with little rainfall.",
        "island": "A piece of land surrounded by water.",
        "valley": "A low area between hills or mountains."
    },
    "fantasy": {
        "dragon": "A mythical fire-breathing creature.",
        "wizard": "A person skilled in magic.",
        "castle": "A fortified building often found in medieval stories.",
        "sword": "A large blade used as a weapon.",
        "goblin": "A small mischievous mythical creature."
    }
}

# ASCII hangman art
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


def choose_category():
    print("Choose a category:\n")
    keys = list(CATEGORIES.keys())
    for i, cat in enumerate(keys, 1):
        print(f"{i}. {cat.capitalize()}")

    print(f"{len(keys) + 1}. Mixed (all categories)")

    while True:
        choice = input("\nEnter your choice: ").strip()
        if not choice.isdigit():
            print("Enter a number.")
            continue

        idx = int(choice)
        if 1 <= idx <= len(keys):
            return keys[idx - 1], CATEGORIES[keys[idx - 1]]
        elif idx == len(keys) + 1:
            # Combine all categories into one large pool
            mixed = {}
            for cat_dict in CATEGORIES.values():
                mixed.update(cat_dict)
            return "mixed", mixed
        else:
            print("Invalid choice. Try again.")


def choose_word(category_dict):
    return random.choice(list(category_dict.keys()))


def display_state(word, guessed_letters, wrong_guesses):
    print(HANGMAN_PICS[wrong_guesses])
    print("\nWord: ", end="")
    revealed = [letter if letter in guessed_letters else "_" for letter in word]
    print(" ".join(revealed))
    print("Guessed letters: ", " ".join(sorted(guessed_letters)))
    print()


def hangman():
    print("=== HANGMAN WITH CATEGORIES ===")
    print("Guess the word one letter at a time.")
    print("Type 'hint' for a definition, 'quit' to exit.\n")

    category_name, category_dict = choose_category()
    print(f"\nSelected category: {category_name.capitalize()}\n")

    word = choose_word(category_dict)
    definition = category_dict[word]

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
                print("Hint:", definition)
                hint_used = True
            else:
                print("You already used your hint.")
            continue

        if len(guess) != 1 or not guess.isalpha():
            print("Please enter a single letter.")
            continue

        if guess in guessed_letters:
            print("Already guessed.")
            continue

        guessed_letters.add(guess)

        if guess not in word:
            wrong_guesses += 1
            print("Wrong!")

        # Check lose
        if wrong_guesses >= max_wrong:
            display_state(word, guessed_letters, wrong_guesses)
            print(f"You lost! The word was: {word}")
            break

        # Check win
        if all(letter in guessed_letters for letter in word):
            display_state(word, guessed_letters, wrong_guesses)
            print(f"You won! The word was: {word}")
            break


if __name__ == "__main__":
    try:
        hangman()
    except KeyboardInterrupt:
        print("\nExiting…")
        sys.exit(0)

