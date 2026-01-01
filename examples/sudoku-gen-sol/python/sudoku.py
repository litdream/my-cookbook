import random

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
    
    # Fill diagonal 3x3 boxes
    for i in range(0, 9, 3):
        fill_box(board, i, i)

    # Solve the full board
    solve_sudoku(board)
    
    # Create a copy for the puzzle
    puzzle = [row[:] for row in board]

    # Remove some numbers to create a puzzle
    squares_to_remove = 40  # Adjust difficulty
    while squares_to_remove > 0:
        row = random.randint(0, 8)
        col = random.randint(0, 8)
        if puzzle[row][col] != 0:
            num = puzzle[row][col]
            puzzle[row][col] = 0
            # Check if the puzzle still has a unique solution (basic check)
            temp_board = [r[:] for r in puzzle]
            solutions_found = [0]
            count_solutions(temp_board, solutions_found)
            if solutions_found[0] != 1:
                puzzle[row][col] = num # Revert if not unique
            else:
                squares_to_remove -= 1
    
    return puzzle

def fill_box(board, row_start, col_start):
    nums = list(range(1, 10))
    random.shuffle(nums)
    for i in range(3):
        for j in range(3):
            board[row_start + i][col_start + j] = nums.pop()

def count_solutions(board, count):
    find = find_empty(board)
    if not find:
        count[0] += 1
        return
    
    row, col = find
    for i in range(1, 10):
        if is_valid(board, i, (row, col)):
            board[row][col] = i
            count_solutions(board, count)
            board[row][col] = 0

def print_board(board):

    print("    1 2 3   4 5 6   7 8 9")

    print("  +-------+-------+-------+")

    for i in range(len(board)):

        if i % 3 == 0 and i != 0:

            print("  +-------+-------+-------+")



        print(f"{i+1} | ", end="") # Row number

        for j in range(len(board[0])):

            if j % 3 == 0 and j != 0:

                print("| ", end="")



            if board[i][j] == 0:

                print(". ", end="")

            else:

                print(str(board[i][j]) + " ", end="")

        print("|")

    print("  +-------+-------+-------+")

def play_sudoku():
    print("Generating Sudoku Board...")
    original_puzzle = generate_sudoku()
    board = [row[:] for row in original_puzzle] # Copy for playing
    
    while True:
        print("\nGenerated Sudoku Board:")
        print_board(board)
        
        if find_empty(board) is None:
            print("Congratulations! You solved the Sudoku!")
            break

        command = input("Enter your move (row col value), 'solve' to see solution, or 'quit' to exit: ").lower().strip()
        
        if command == 'quit':
            print("Exiting Sudoku.")
            break
        elif command == 'solve':
            solution_board = [row[:] for row in original_puzzle] # Use original puzzle for solving
            if solve_sudoku(solution_board):
                print("\nSolution:")
                print_board(solution_board)
            else:
                print("Could not find a solution for the original puzzle.")
            break
        
        try:
            parts = command.split()
            if len(parts) != 3:
                raise ValueError("Invalid input format. Use 'row col value'.")
                
            row, col, value = map(int, parts)
            
            # Adjust to 0-based indexing
            row -= 1
            col -= 1
            
            if not (0 <= row < 9 and 0 <= col < 9 and 1 <= value <= 9):
                raise ValueError("Row, column must be between 1-9, and value between 1-9.")
            
            if original_puzzle[row][col] != 0: # Check if it's a pre-filled cell
                print("Cannot change pre-filled numbers!")
                continue

            if is_valid(board, value, (row, col)):
                board[row][col] = value
            else:
                print(f"Invalid move: {value} cannot be placed at ({row+1}, {col+1})")
        except ValueError as e:
            print(f"Error: {e}")
        except IndexError:
            print("Error: Row or column out of bounds. Please use numbers between 1 and 9.")

if __name__ == "__main__":
    play_sudoku()