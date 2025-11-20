#!/usr/bin/env python3
import random
import sys

# ================================
# WORDS WITH DEFINITIONS
# ================================
WORD_DEFS = {
    # Programming
    "python": "A popular programming language known for readability.",
    "variable": "A named place in memory that stores a value.",
    "function": "A reusable block of code that performs an action.",
    "object": "An instance of a class in object-oriented programming.",
    "syntax": "The rules defining how code must be written.",
    "library": "A collection of code modules or functions.",
    "keyboard": "A device with keys used to input text into a computer.",
    "monitor": "A screen that displays output from a computer.",
    "battery": "A device that stores energy and powers electronics.",
    "algorithm": "A step-by-step procedure to solve a problem.",
    "array": "An ordered collection of elements of the same type.",
    "compiler": "A program that converts source code into executable code.",
    "database": "An organized collection of data stored electronically.",
    "variable": "A symbolic name representing a value stored in memory.",
    "integer": "A whole number, positive or negative, including zero.",
    "boolean": "A data type with only two possible values: True or False.",
    "module": "A file containing Python definitions and functions.",
    "package": "A collection of Python modules in a directory.",
    
    # Animals
    "elephant": "A large mammal with a trunk.",
    "giraffe": "A tall African mammal with a very long neck.",
    "dolphin": "A highly intelligent marine mammal.",
    "penguin": "A flightless bird that lives in cold regions.",
    "kangaroo": "A jumping marsupial from Australia.",
    "lion": "The large cat known as the king of the jungle.",
    "tiger": "A large striped feline found in Asia.",
    "bear": "A large omnivorous mammal.",
    "wolf": "A carnivorous mammal that lives in packs.",
    "fox": "A small, cunning carnivorous mammal.",
    "eagle": "A bird of prey with excellent vision.",
    
    # Countries
    "canada": "A country in North America known for its forests and lakes.",
    "brazil": "A large South American country famous for the Amazon rainforest.",
    "france": "A European country known for wine, cheese, and the Eiffel Tower.",
    "germany": "A European country known for cars, beer, and history.",
    "india": "A South Asian country famous for spices, culture, and the Taj Mahal.",
    "japan": "An island nation in East Asia known for technology and sushi.",
    "egypt": "A country in North Africa famous for the Pyramids.",
    
    # Fruits
    "apple": "A round fruit that is usually red, green, or yellow.",
    "banana": "A long, yellow fruit that is sweet when ripe.",
    "orange": "A citrus fruit known for its bright color and vitamin C.",
    "mango": "A tropical fruit with sweet, juicy flesh.",
    "pear": "A sweet fruit with a rounded base and tapering top.",
    "grape": "A small, juicy fruit often used to make wine.",
    "pineapple": "A tropical fruit with spiky skin and sweet yellow flesh.",
    
    # Sports
    "soccer": "A sport played by two teams of eleven players with a round ball.",
    "basketball": "A game played by two teams where the goal is to shoot a ball through a hoop.",
    "tennis": "A sport where players use rackets to hit a ball over a net.",
    "volleyball": "A sport where two teams hit a ball over a net trying to land it on the opponent’s side.",
    "swimming": "The activity of moving through water using your body.",
    "boxing": "A combat sport where two participants throw punches at each other.",
    
    # Miscellaneous
    "planet": "A celestial body orbiting a star.",
    "gravity": "A natural force that attracts bodies toward one another.",
    "rhythm": "A strong, repeated pattern of movement or sound.",
    "window": "An opening in a wall to let in light or air.",
    "castle": "A fortified building from medieval times.",
    "forest": "A large area covered chiefly with trees and undergrowth.",
    "dragon": "A mythical creature that breathes fire in many stories.",
    "mountain": "A large natural elevation of Earth's surface.",
    "river": "A natural flowing watercourse that usually flows into a sea.",
    "silver": "A precious metal with atomic number 47."
}

WORD_LIST = list(WORD_DEFS.keys())

# ================================
# Jumble functions
# ================================
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
