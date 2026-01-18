# MinMax Algorithm for TicTacToe CPU player

https://www.youtube.com/watch?v=LbTu0rwikwg


## Branch strategy.

This will make decision in terms of CPU:

Assume:  CPU(X),  Human(O)
  - Basically, depth first search: 
    - Going through all board, for CPU(X)

Pseudocode:
```
FUNCTION minimax(board, is_maximizing):
    IF game_is_over:
        RETURN score ( +10, -10, or 0 )

    IF is_maximizing:
        best_score = -infinity
        FOR each empty spot:
            place "X"
            score = minimax(board, false)  // Now simulate the human's turn
            remove "X" (backtrack)
            best_score = max(best_score, score)
        RETURN best_score

    ELSE (is_minimizing):
        best_score = +infinity
        FOR each empty spot:
            place "O"
            score = minimax(board, true)   // Now simulate the AI's turn
            remove "O" (backtrack)
            best_score = min(best_score, score)
        RETURN best_score
```

So, each search will find if this leads to a WIN (+10),
and maintains that state for chosen path.
