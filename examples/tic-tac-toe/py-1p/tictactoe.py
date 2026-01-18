#!/usr/bin/env python3

from abc import ABC, abstractmethod
import math

class Board:
    def __init__(self):
        self.board = [
            [ '-', '-', '-' ],
            [ '-', '-', '-' ],
            [ '-', '-', '-' ],
        ]

    def __str__(self):
        rtn = [ '-------------' ]
        for row in self.board:
            line = ['|']
            for col in row:
                line.append(col)
                line.append('|')
            rtn.append(' '.join(line))
            rtn.append( '-------------' )
        return '\n'.join(rtn)

    def is_valid_move(self, r:int, c:int):
        if 0 <= r < 3 and 0 <= c < 3:
            return self.board[r][c] == '-'
        return False

    def place_move(self, r:int, c:int, player_symbol:str):
        """Put user move into the board
        PRE: is_valid_move() is *True*
        """
        self.board[r][c] = player_symbol

    def check_win(self) -> str:
        """
        Return Winner, or "" for not yet.
        """
        
        # Row check
        for i in range(3):
            if self.board[i][0] != '-' and self.board[i][0] == self.board[i][1] == self.board[i][2]:
                return self.board[i][0]
                
        # Column check
        for j in range(3):
            if self.board[0][j] != '-' and self.board[0][j] == self.board[1][j] == self.board[2][j]:
                return self.board[0][j]
                
        # Diag check
        if self.board[0][0] != '-' and self.board[0][0] == self.board[1][1] == self.board[2][2]:
            return self.board[0][0]
        if self.board[0][2] != '-' and self.board[0][2] == self.board[1][1] == self.board[2][0]:
            return self.board[0][2]
        return ""
    def board_full(self):         
        flattened = [item for row in self.board for item in row]
        return '-' not in flattened

    

# The interface (Abstract Base Class)
class Player(ABC):
    @abstractmethod
    def make_move(self, board):
        pass

# Human Player
class HumanPlayer(Player):
    def __init__(self, my_symbol):
        self.symbol = my_symbol

    def make_move(self, board):
        while True:
            try:
                prompt = f"Player {self.symbol}, enter your move (X and Y, e.g., 1 2): "
                user_input = input(prompt).split()
                
                # Adjust for 0-based indexing
                y = int(user_input[0]) - 1     # row
                x = int(user_input[1]) - 1     # col
                row, col = y, x
                
                if board.is_valid_move(row, col):
                    board.place_move(row, col, self.symbol)
                    break
                else:
                    print("Invalid move. Try again.")
                    
            except (ValueError, IndexError):
                print("Please enter two numbers separated by a space (e.g., 1 2).")    


class AIPlayer(Player):
    def __init__(self, ai_player_symbol, opponent_symbol):
        self.symbol = ai_player_symbol
        self.opponent_symbol = opponent_symbol

    def make_move(self, board):
        print(f"AI Player {self.symbol} is thinking...")
        best_move = self._find_best_move(board)
        if best_move != (-1, -1):
            board.place_move(best_move[0], best_move[1], self.symbol)

    def _find_best_move(self, board):
        best_val = -math.inf
        best_move = (-1, -1)

        for i in range(3):
            for j in range(3):
                if board.is_valid_move(i, j):
                    # Make the move
                    board.place_move(i, j, self.symbol)
                    
                    # Compute evaluation function for this move
                    move_val = self._minimax(board, 0, False)
                    
                    # Undo the move
                    board.place_move(i, j, '-')

                    if move_val > best_val:
                        best_val = move_val
                        best_move = (i, j)
        return best_move

    def _minimax(self, board, depth, is_maximizing):
        score = self._evaluate(board)

        # Terminal states: Win, Loss, or Tie
        if score == 10: return score
        if score == -10: return score
        if board.board_full(): return 0

        if is_maximizing:
            best = -math.inf
            for i in range(3):
                for j in range(3):
                    if board.is_valid_move(i, j):
                        board.place_move(i, j, self.symbol)
                        best = max(best, self._minimax(board, depth + 1, not is_maximizing))
                        board.place_move(i, j, '-')
            return best
        else:
            best = math.inf
            for i in range(3):
                for j in range(3):
                    if board.is_valid_move(i, j):
                        board.place_move(i, j, self.opponent_symbol)
                        best = min(best, self._minimax(board, depth + 1, not is_maximizing))
                        board.place_move(i, j, '-')
            return best

    def _evaluate(self, board):
        # Rows and Columns
        for i in range(3):
            # Check Rows
            if board.board[i][0] == board.board[i][1] == board.board[i][2] != '-':
                return 10 if board.board[i][0] == self.symbol else -10
            # Check Columns
            if board.board[0][i] == board.board[1][i] == board.board[2][i] != '-':
                return 10 if board.board[0][i] == self.symbol else -10

        # Diagonals
        if board.board[0][0] == board.board[1][1] == board.board[2][2] != '-':
            return 10 if board.board[0][0] == self.symbol else -10
            
        if board.board[0][2] == board.board[1][1] == board.board[2][0] != '-':
            return 10 if board.board[0][2] == self.symbol else -10

        return 0                


## MAIN
def main():
    print("Hello, Tic-Tac-Toe!")
    
    board = Board()
    
    # Setup Player 1 (Always Human 'X')
    player1 = HumanPlayer('X')
    
    print("Choose opponent: (1) Human or (2) AI")
    try:
        choice = int(input().strip())
    except ValueError:
        choice = 1 # Default to human if input is invalid

    # Setup Player 2
    if choice == 1:
        player2 = HumanPlayer('O')
    else:
        # AI plays as 'O', assumes opponent is 'X'
        player2 = AIPlayer(ai_player_symbol='O', opponent_symbol='X')

    current_player_symbol = 'X'
    current_player = player1

    # Main Game Loop
    while True:
        #board.print_board()
        print(board)
        current_player.make_move(board)

        if board.check_win() != '':
            #board.print_board()
            print(board)
            
            print(f"Player {current_player.symbol} wins!")
            break
            
        if board.board_full():
            #board.print_board()
            print(board)
            
            print("It's a draw!")
            break

        # Switch players using Python's "if-else expression" or standard if
        if current_player == player1:
            current_player = player2
        else:
            current_player = player1

if __name__ == "__main__":
    main()    
