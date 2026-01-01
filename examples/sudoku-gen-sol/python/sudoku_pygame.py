import pygame
import random
import sys

# --- Core Sudoku Logic (from previous script) ---

def solve_sudoku(board):
    find = find_empty(board)
    if not find:
        return True
    else:
        row, col = find

    for i in range(1, 10):
        if is_valid(board, i, (row, col)):
            board[row][col] = i
            if solve_sudoku(board):
                return True
            board[row][col] = 0
    return False

def is_valid(board, num, pos):
    # Check row
    for i in range(len(board[0])):
        if board[pos[0]][i] == num and pos[1] != i:
            return False
    # Check column
    for i in range(len(board)):
        if board[i][pos[1]] == num and pos[0] != i:
            return False
    # Check 3x3 box
    box_x = pos[1] // 3
    box_y = pos[0] // 3
    for i in range(box_y * 3, box_y * 3 + 3):
        for j in range(box_x * 3, box_x * 3 + 3):
            if board[i][j] == num and (i, j) != pos:
                return False
    return True

def find_empty(board):
    for r in range(len(board)):
        for c in range(len(board[0])):
            if board[r][c] == 0:
                return (r, c)
    return None

def generate_sudoku():
    board = [[0 for _ in range(9)] for _ in range(9)]
    for i in range(0, 9, 3):
        fill_box(board, i, i)
    
    solution = [row[:] for row in board]
    solve_sudoku(solution)
    
    puzzle = [row[:] for row in solution]
    squares_to_remove = 45
    while squares_to_remove > 0:
        row = random.randint(0, 8)
        col = random.randint(0, 8)
        if puzzle[row][col] != 0:
            puzzle[row][col] = 0
            squares_to_remove -= 1
            
    return puzzle, solution

def fill_box(board, row_start, col_start):
    nums = list(range(1, 10))
    random.shuffle(nums)
    for i in range(3):
        for j in range(3):
            board[row_start + i][col_start + j] = nums.pop()

# --- Pygame Setup ---
pygame.init()
pygame.font.init()

# Constants
SCREEN_WIDTH = 540
SCREEN_HEIGHT = 600
GRID_SIZE = 540 
CELL_SIZE = GRID_SIZE // 9

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
BLUE = (173, 216, 230) # For selected cell
RED = (255, 0, 0)
YELLOW = (255, 255, 0) # For incorrect guess

# Fonts
NUMBER_FONT = pygame.font.SysFont('Arial', 40)
STATUS_FONT = pygame.font.SysFont('Arial', 24)


class SudokuGrid:
    def __init__(self, screen, puzzle, solution):
        self.screen = screen
        self.puzzle = puzzle
        self.solution = solution
        self.grid = [row[:] for row in puzzle] # User's grid
        self.selected = None
        self.incorrect_cells = set()

    def draw(self):
        self.screen.fill(WHITE)
        self.draw_grid_lines()
        self.draw_numbers()
        self.highlight_selected()

    def draw_grid_lines(self):
        for i in range(10):
            thick = 4 if i % 3 == 0 else 1
            # Vertical lines
            pygame.draw.line(self.screen, BLACK, (i * CELL_SIZE, 0), (i * CELL_SIZE, GRID_SIZE), thick)
            # Horizontal lines
            pygame.draw.line(self.screen, BLACK, (0, i * CELL_SIZE), (GRID_SIZE, i * CELL_SIZE), thick)
            
    def draw_numbers(self):
       for r in range(9):
           for c in range(9):
                # Draw incorrect background first
                if (r, c) in self.incorrect_cells:
                    pygame.draw.rect(self.screen, YELLOW, (c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE))

                num = self.grid[r][c]
                if num != 0:
                    color = BLACK if self.puzzle[r][c] != 0 else BLUE # Original numbers vs user numbers
                    text = NUMBER_FONT.render(str(num), True, color)
                    self.screen.blit(text, (c * CELL_SIZE + (CELL_SIZE//2 - text.get_width()//2),
                                            r * CELL_SIZE + (CELL_SIZE//2 - text.get_height()//2)))

    def highlight_selected(self):
        if self.selected:
            r, c = self.selected
            pygame.draw.rect(self.screen, RED, (c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE), 4)

    def select(self, row, col):
        if 0 <= row < 9 and 0 <= col < 9:
            self.selected = (row, col)

    def place_number(self, value):
        if not self.selected:
            return
        
        r, c = self.selected
        # Can only place numbers in empty cells of the original puzzle
        if self.puzzle[r][c] == 0:
            if self.solution[r][c] == value:
                self.grid[r][c] = value
                if (r, c) in self.incorrect_cells:
                    self.incorrect_cells.remove((r, c))
            else:
                self.grid[r][c] = 0 # Or you can show the wrong number temporarily
                self.incorrect_cells.add((r,c))


def main():
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("Sudoku")
    
    puzzle, solution = generate_sudoku()
    grid = SudokuGrid(screen, puzzle, solution)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            
            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                if y < GRID_SIZE:
                    row = y // CELL_SIZE
                    col = x // CELL_SIZE
                    grid.select(row, col)
            
            if event.type == pygame.KEYDOWN:
                if event.key in [pygame.K_1, pygame.K_2, pygame.K_3, pygame.K_4, pygame.K_5, pygame.K_6, pygame.K_7, pygame.K_8, pygame.K_9]:
                    num = int(pygame.key.name(event.key))
                    grid.place_number(num)

        grid.draw()
        pygame.display.flip()

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
