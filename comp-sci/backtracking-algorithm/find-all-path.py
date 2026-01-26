"""
Problem:  Find all path, for NxN grid.
Imagine a small 3x3 grid.  You want to get from the top-left to the
bottom-right, but you can only move Right or Down.

"""


def find_paths(n):
    def backtrack(r, c, current_path):
        # 1. BASE CASE: If we reached the target (bottom-right corner)
        if r == n - 1 and c == n - 1:
            all_paths.append(list(current_path)) # Store a copy of the successful path
            return

        # 2. EXPLORE: Try moving RIGHT
        if c + 1 < n:
            current_path.append((r, c + 1))  # STEP FORWARD
            backtrack(r, c + 1, current_path) # RECURSE (Go deeper)
            current_path.pop()               # BACKTRACK (Undo the step)

        # 3. EXPLORE: Try moving DOWN
        if r + 1 < n:
            current_path.append((r + 1, c))  # STEP FORWARD
            backtrack(r + 1, c, current_path) # RECURSE (Go deeper)
            current_path.pop()               # BACKTRACK (Undo the step)

    all_paths = []
    # Start at the top-left corner (0,0)
    backtrack(0, 0, [(0, 0)])
    return all_paths

# Example for a 3x3 grid
n = 3
results = find_paths(n)

print(f"Total paths for {n}x{n}: {len(results)}")
for i, path in enumerate(results):
    print(f"Path {i+1}: {path}")
