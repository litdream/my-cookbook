"""
Hangman CLI game.
Good Sample Output:  from Gemini's prototype

```
=== HANGMAN ===
Guess the word one letter at a time.
Type 'hint' for a definition, 'quit' to exit.


     +---+
         |
         |
         |
       ===

Word: _ _ _ _ _ _
Guessed letters:

Your guess:
```

"""


import os, sys
import random
from typing import Tuple

# Word list with hints
words = [
    ("python", "A programming language known for its readability."),
    ("gravity", "A natural force that pulls objects toward each other."),
    ("castle", "A large fortified building from medieval times."),
    ("keyboard", "A device with keys used to type."),
    ("forest", "A large area covered mostly with trees."),
    ("planet", "A celestial body orbiting a star."),
    ("battery", "A portable power source."),
    ("mountain", "A large natural elevation of the Earth's surface."),
    ("library", "A place where books are kept."),
    ("rhythm", "A repeated pattern of movement or sound.")
]

# Hangman drawings
hangman_pics = [
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

def choose_word() -> Tuple[str, str]:
    return random.choice(words)

class Hangman:
    def __init__(self):
        self.secret, self.hint = choose_word()
        self.guessed = []
        self.wrong: int = 0

    def display_game_state(self):
        print( hangman_pics[self.wrong])
        print( f"\nWord: {self.secret_spaced()}")
        print( f"Guessed letters: {' '.join(sorted(self.guessed))}")

    def secret_spaced(self) -> str:
        lst = []
        for sc in self.secret:    # sc := secret_char
            if sc in self.guessed:
                lst.append(sc)
            else:
                lst.append("_")
        return ' '.join(lst)

    def win(self) -> bool:
        for sc in self.secret:
            if sc not in self.guessed:
                return False
        return True
    
    def lost(self) -> bool:
        return self.wrong >= len(hangman_pics)
    

def main():
    print(" == HANGMAN Game ==")

    # Init
    game = Hangman()
    while not (game.win() or game.lost()):
        game.display_game_state()
        try:
            user_input = input("\nYour guess: ")
        except EOFError:
            # Handle Ctrl-D
            break

        user_input = user_input.strip()
        if len(user_input) != 1:
            print("I said: SINGLE CHAR!!")
            continue

        guess = user_input[0].lower()
        if guess in game.guessed:
            print(f"Char({guess}) is already guessed. Try again.")
            continue

        game.guessed.append(guess)
        if guess not in game.secret:
            game.wrong += 1

    if game.win():
        print("Congratulations!  You won.")
    elif game.lost():
        print(f"Sorry.  The word was: {game.secret}")
    else:
        #unlikely
        print("Should not reach here.")
        

if __name__ == '__main__':
    main()
