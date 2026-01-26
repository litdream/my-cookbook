def solve_n_queens(n=8):
    # Initialize an empty board
    board = [["." for _ in range(n)] for _ in range(n)]
    solutions = []

    def is_valid(r, c):
        # 1. Check Column (We don't need to check rows because we place one per row)
        for i in range(r):
            if board[i][c] == "Q":
                return False
        
        # 2. Check Upper-Left Diagonal
        i, j = r, c
        while i >= 0 and j >= 0:
            if board[i][j] == "Q":
                return False
            i -= 1
            j -= 1
            
        # 3. Check Upper-Right Diagonal
        i, j = r, c
        while i >= 0 and j < n:
            if board[i][j] == "Q":
                return False
            i -= 1
            j += 1
            
        return True

    def backtrack(r):
        # BASE CASE: All queens placed (reached past the last row)
        if r == n:
            # Join the rows into strings for a nice visual output
            copy = [" ".join(row) for row in board]
            solutions.append(copy)
            return

        for c in range(n):
            if is_valid(r, c):
                # 1. THE STEP: Place the queen
                board[r][c] = "Q"

                # 2. THE SEARCH: Move to the next row
                backtrack(r + 1)

                # 3. THE BACKTRACK: Remove the queen to try the next column
                board[r][c] = "."

    backtrack(0)
    return solutions

# Run for 8x8
all_solutions = solve_n_queens(8)

print(f"Total solutions for 8x8: {len(all_solutions)}")
print("\nFirst Solution Found:")
for row in all_solutions[0]:
    print(row)
