#!/usr/bin/env python3
import random
import time
import os
import sys

# =========================
#   WORD CATEGORIES
# =========================
CATEGORIES = {
    "Animals": [
        "elephant", "giraffe", "tiger", "penguin", "kangaroo",
        "alligator", "dolphin", "hamster", "ostrich", "jaguar"
    ],
    "Countries": [
        "canada", "brazil", "france", "germany", "norway",
        "india", "japan", "chile", "egypt", "sweden"
    ],
    "Fruits": [
        "banana", "mango", "avocado", "pineapple", "papaya",
        "grape", "strawberry", "peach", "blueberry", "watermelon"
    ],
    "Programming": [
        "variable", "function", "object", "method", "package",
        "integer", "boolean", "syntax", "iterator", "exception"
    ],
}

# =========================
#  HANGMAN DRAWING FRAMES  
# =========================

HANGMAN_FRAMES = [
    """
    
    
    
    
    =========
    """,
    """
      |
      |
      |
      |
      |
    =========
    """,
    """
      +---.
      |
      |
      |
      |
    =========
    """,
    """
      +---.
      |   O
      |
      |
      |
    =========
    """,
    """
      +---.
      |   O
      |   |
      |
      |
    =========
    """,
    """
      +---.
      |   O
      |  /|
      |
      |
    =========
    """,
    """
      +---.
      |   O
      |  /|\\
      |
      |
    =========
    """,
    """
      +---.
      |   O
      |  /|\\
      |  /
      |
    =========
    """,
    """
      +---.
      |   O
      |  /|\\
      |  / \\
      |
    =========
    """
]

MAX_WRONG = len(HANGMAN_FRAMES) - 1


def clear():
    os.system("cls" if os.name == "nt" else "clear")


# =========================
# ANIMATIONS
# =========================

FR_SLEEP = 0.3

def animate_frame(index):
    """Draw hangman with a small animation step."""
    clear()
    print(HANGMAN_FRAMES[index])
    time.sleep(FR_SLEEP)


def animate_progress(wrong_guesses):
    """Play all frames up to wrong_guesses quickly to show a build animation."""
    for i in range(wrong_guesses + 1):
        animate_frame(i)


def animate_victory():
    frames = [
        r"""
   \o/ 
    |  
   / \   
You survived!
""",
        r"""
   o  
  /|\  
  / \  
You survived!
"""
    ]
    for _ in range(4):
        for f in frames:
            clear()
            print(f)
            time.sleep(0.4)


def animate_defeat(word):
    frames = [
        f"""
   +---.
   |   O
   |  /|\\
   |  / \\
   |
 =========
 You died... The word was: {word}
""",
        f"""
   +---.
   |   O
   |  /|\\
   |  / \\
   |
 =========
 Game Over... The word was: {word}
"""
    ]
    for _ in range(4):
        for f in frames:
            clear()
            print(f)
            time.sleep(FR_SLEEP)


# =========================
# GAME LOGIC
# =========================

def pick_category():
    print("Choose a category:")
    keys = list(CATEGORIES.keys())
    for i, c in enumerate(keys, 1):
        print(f"{i}. {c}")

    while True:
        choice = input("Your choice: ").strip()
        if choice.isdigit() and 1 <= int(choice) <= len(keys):
            return keys[int(choice) - 1]
        print("Invalid selection.")


def play_game():
    clear()
    print("=== HANGMAN ===\n")

    category = pick_category()
    word = random.choice(CATEGORIES[category]).lower()
    guessed = set()
    wrong = 0

    while True:
        clear()

        # draw current frame
        print(f"Category: {category}\n")
        print(HANGMAN_FRAMES[wrong])

        # display puzzle
        display = " ".join([letter if letter in guessed else "_" for letter in word])
        print("\nWord: ", display)

        print(f"\nWrong guesses: {wrong}/{MAX_WRONG}")
        print("Guessed letters:", " ".join(sorted(guessed)) or "(none)")

        # win condition
        if all(letter in guessed for letter in word):
            animate_victory()
            return

        # lose condition
        if wrong >= MAX_WRONG:
            animate_defeat(word)
            return

        guess = input("\nEnter a letter: ").lower().strip()
        if len(guess) != 1 or not guess.isalpha():
            print("Please enter one letter.")
            time.sleep(1)
            continue

        if guess in guessed:
            print("Already guessed.")
            time.sleep(1)
            continue

        guessed.add(guess)

        if guess not in word:
            wrong += 1
            animate_progress(wrong)


def main():
    while True:
        play_game()
        again = input("\nPlay again? (y/n) ").lower().strip()
        if again != "y":
            break
    print("Goodbye!")


if __name__ == "__main__":
    main()

