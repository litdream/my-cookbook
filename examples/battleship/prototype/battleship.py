#!/usr/bin/env python3
"""
CLI Battleship (single-player vs computer)

Usage: python3 battleship.py
Enter coordinates like A5, b10, etc. Type "quit" to exit.
"""

import random
import string
import sys

# -------- Configurable defaults --------
DEFAULT_ROWS = 8
DEFAULT_COLS = 8

# Standard ships (name: length). We'll choose a subset that fits the board.
STANDARD_SHIPS = [
    ("Carrier", 5),
    ("Battleship", 4),
    ("Cruiser", 3),
    ("Submarine", 3),
    ("Destroyer", 2),
]


# -------- Helper utilities --------
def clamp_ships_to_board(rows, cols):
    """Return a list of ships that will reasonably fit in the board."""
    # Start with largest ships first, add ships until board area can't fit them
    area = rows * cols
    chosen = []
    used = 0
    for name, length in STANDARD_SHIPS:
        # crude check: require at least length cells per ship (ignores adjacency constraints)
        if used + length <= area:
            chosen.append((name, length))
            used += length
    # If nothing chosen (tiny board), force one small ship
    if not chosen:
        chosen = [("Mini", min(2, max(1, min(rows, cols))))]
    return chosen


def coords_to_index(coord_str, rows, cols):
    """Convert coordinate like 'A5' -> (row_index, col_index). Return None on invalid."""
    coord = coord_str.strip().upper()
    if coord == "":
        return None
    # split letters and digits
    letters = ''.join(ch for ch in coord if ch.isalpha())
    digits = ''.join(ch for ch in coord if ch.isdigit())
    if not letters or not digits:
        return None
    # convert row letters (allow multi-letter rows like 'AA' if board huge)
    row_num = 0
    for ch in letters:
        row_num = row_num * 26 + (ord(ch) - ord('A') + 1)
    row_idx = row_num - 1
    try:
        col_idx = int(digits) - 1
    except ValueError:
        return None
    if 0 <= row_idx < rows and 0 <= col_idx < cols:
        return (row_idx, col_idx)
    return None


def index_to_coords(r, c):
    """Convert numeric indices to coordinate string like 'A5'."""
    # convert row index to letters (A, B, ..., Z, AA, AB, ...)
    n = r + 1
    letters = ""
    while n > 0:
        n, rem = divmod(n - 1, 26)
        letters = chr(ord('A') + rem) + letters
    return f"{letters}{c+1}"


# -------- Board & Ship classes --------
class Ship:
    def __init__(self, name, length, coords):
        self.name = name
        self.length = length
        self.coords = set(coords)  # set of (r,c)
        self.hits = set()

    def is_sunk(self):
        return self.hits >= self.coords

    def register_hit(self, coord):
        if coord in self.coords:
            self.hits.add(coord)
            return True
        return False


class Board:
    def __init__(self, rows=DEFAULT_ROWS, cols=DEFAULT_COLS, ships_spec=None):
        self.rows = rows
        self.cols = cols
        self.ships = []
        self.shots = {}  # (r,c) -> 'hit'/'miss'
        if ships_spec is None:
            ships_spec = clamp_ships_to_board(rows, cols)
        self._place_ships_randomly(ships_spec)

    def _place_ships_randomly(self, ships_spec):
        """Place ships randomly on the board without overlapping."""
        occupied = set()
        attempts = 0
        for name, length in ships_spec:
            placed = False
            while not placed:
                attempts += 1
                if attempts > 2000:
                    raise RuntimeError("Failed to place ships, try a different board size.")
                orientation = random.choice(['H', 'V'])
                if orientation == 'H':
                    r = random.randint(0, self.rows - 1)
                    c = random.randint(0, self.cols - length)
                    coords = [(r, c + i) for i in range(length)]
                else:
                    r = random.randint(0, self.rows - length)
                    c = random.randint(0, self.cols - 1)
                    coords = [(r + i, c) for i in range(length)]

                if any(coord in occupied for coord in coords):
                    continue  # overlap, try new position

                # place ship
                self.ships.append(Ship(name, length, coords))
                for coord in coords:
                    occupied.add(coord)
                placed = True

    def receive_shot(self, r, c):
        """Process a shot at (r,c). Return tuple (result, ship_name or None).
        result: 'miss', 'hit', 'sunk', 'repeat' """
        coord = (r, c)
        if coord in self.shots:
            return ('repeat', None)

        # check ships
        for ship in self.ships:
            if coord in ship.coords:
                ship.register_hit(coord)
                self.shots[coord] = 'hit'
                if ship.is_sunk():
                    return ('sunk', ship.name)
                return ('hit', ship.name)

        # miss
        self.shots[coord] = 'miss'
        return ('miss', None)

    def all_sunk(self):
        return all(ship.is_sunk() for ship in self.ships)

    def visible_shot_board(self):
        """Return 2D list for display: '~' water unknown, 'O' miss, 'X' hit"""
        grid = [['~' for _ in range(self.cols)] for _ in range(self.rows)]
        for (r, c), res in self.shots.items():
            grid[r][c] = 'X' if res == 'hit' else 'O'
        return grid

    # Optional debug helper
    def reveal_ships_board(self):
        """Return a 2D list showing ships (S), hits (X), and misses (O)."""
        grid = [['~' for _ in range(self.cols)] for _ in range(self.rows)]
        for ship in self.ships:
            for (r, c) in ship.coords:
                grid[r][c] = 'S'
            for (r, c) in ship.hits:
                grid[r][c] = 'X'
        for (r, c), res in self.shots.items():
            if res == 'miss':
                grid[r][c] = 'O'
        return grid


# -------- UI / Game loop --------
def print_board_grid(grid):
    """Pretty-print a grid (2D list)."""
    rows = len(grid)
    cols = len(grid[0]) if rows else 0
    # header: column numbers
    header_nums = '    ' + ' '.join(f"{i+1:>2}" for i in range(cols))
    print(header_nums)
    for r in range(rows):
        row_label = index_to_row_label(r)
        row_cells = ' '.join(f" {cell}" if len(cell) == 1 else cell for cell in grid[r])
        print(f"{row_label:>3} {row_cells}")


def index_to_row_label(r):
    # helper: same as index_to_coords row part
    n = r + 1
    letters = ""
    while n > 0:
        n, rem = divmod(n - 1, 26)
        letters = chr(ord('A') + rem) + letters
    return letters


def choose_board_size():
    print("Welcome to Battleship! Default board is 8x8.")
    while True:
        raw = input("Enter board size (rows cols) or press Enter for default (e.g. '8 8'): ").strip()
        if raw == "":
            return DEFAULT_ROWS, DEFAULT_COLS
        parts = raw.split()
        if len(parts) == 2 and parts[0].isdigit() and parts[1].isdigit():
            r = int(parts[0])
            c = int(parts[1])
            if 4 <= r <= 12 and 4 <= c <= 12:
                return r, c
            else:
                print("Please choose rows and cols between 4 and 12.")
                continue
        print("Invalid input. Example valid input: 7 7")


def print_help():
    print("Commands / Input:")
    print("  - Enter coordinates like A5 or b10 to fire.")
    print("  - Type 'reveal' to reveal ship placement (debug).")
    print("  - Type 'quit' to exit.")
    print("  - Type 'help' to see this message again.")


def game_loop():
    rows, cols = choose_board_size()
    ships_spec = clamp_ships_to_board(rows, cols)
    print(f"Placing ships: {', '.join(f'{n}({l})' for n,l in ships_spec)} on a {rows}x{cols} board.")
    board = Board(rows, cols, ships_spec)

    print_help()
    turn = 0
    while True:
        turn += 1
        print("\nYour shots so far:")
        print_board_grid(board.visible_shot_board())

        user = input(f"\nTurn {turn} - Enter coordinate (or 'help'): ").strip()
        if not user:
            continue
        cmd = user.strip().lower()
        if cmd == 'quit':
            print("Goodbye! Exiting game.")
            sys.exit(0)
        if cmd == 'help':
            print_help()
            continue
        if cmd == 'reveal':
            print("\n--- Board (ships revealed) ---")
            print_board_grid(board.reveal_ships_board())
            continue

        coord = coords_to_index(user, rows, cols)
        if coord is None:
            print("Invalid coordinate. Use format like A5. Type 'help' for commands.")
            continue

        r, c = coord
        result, shipname = board.receive_shot(r, c)
        if result == 'repeat':
            print("You already fired at that coordinate. Try again.")
            continue
        elif result == 'miss':
            print(f"Miss at {index_to_coords(r, c)}.")
        elif result == 'hit':
            print(f"Hit! {index_to_coords(r, c)} struck {shipname}!")
        elif result == 'sunk':
            print(f"You sunk the {shipname}! ({index_to_coords(r, c)})")
        else:
            print("Unknown result (internal).")

        if board.all_sunk():
            print("\nCongratulations — you sank all the ships!")
            print(f"You won in {turn} turns.")
            print("\nFinal board (ships revealed):")
            print_board_grid(board.reveal_ships_board())
            break


if __name__ == '__main__':
    try:
        game_loop()
    except KeyboardInterrupt:
        print("\nInterrupted; goodbye.")
        sys.exit(0)
