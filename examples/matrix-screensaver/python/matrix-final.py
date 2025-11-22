#!/usr/bin/env python3

import os, sys
import time
import random
import blessed
term = blessed.Terminal()

PRINTABLE_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?"

GREEN_SHADES = [
    term.color(22),   # Very dark green
    term.color(28),   # Dark green
    term.color(34),   # Medium green
    term.color(40),   # Slightly darker lime
    term.color(46),   # Bright lime green
    term.color(82),   # Brighter green
    term.color(118)
]

MIN_CLOCK = 0.03

def write(txt):
    sys.stdout.write(txt)

def flush():
    sys.stdout.flush()


class Raindrop:
    def __init__(self, term, x):
        self.term = term
        self.x = x
        self.y = random.randint( 0, self.term.height )
        self.length = random.randint( self.term.height // 4, self.term.height // 4 * 3)

        self.chars = list(PRINTABLE_CHARS)
        random.shuffle(self.chars)

        self.last_update_time = time.time()
        self.speed = random.uniform(MIN_CLOCK, 0.2)

    def update(self):
        now = time.time()
        if now - self.last_update_time >= self.speed:
            self.y = (self.y + 1) % self.term.height
            self.last_update_time = now

    def draw(self):
        greens = []
        for gridx in range( self.y-self.length, self.y):
            greens.append( gridx if gridx >=0 else gridx + self.term.height )

        _unit = self.length // 5
        for y in range(self.term.height):
            goto = self.term.move_xy(self.x, y)
            color = self.term.black
            char = self.chars[y]

            if y == self.y:
                color = self.term.white
            elif y in greens:
                _idx = min(greens.index(y) // _unit, len(GREEN_SHADES)-1)
                color = GREEN_SHADES[_idx]
            else:
                char = ' '
            write(goto + color + char )


def main():
    with term.cbreak(), term.hidden_cursor():
        write(term.enter_fullscreen)
        write(term.clear)

        rains = []
        for i in range(term.width):
            if i%2 == 0:
                rains.append( Raindrop(term,i))
        running = True
        while running:

            for r in rains:
                r.update()
                r.draw()
            flush()

            key = term.inkey(timeout=MIN_CLOCK)
            if key:
                running = False

    write(term.exit_fullscreen)
    sys.exit(0)

if __name__ == '__main__':
    main()
