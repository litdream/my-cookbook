import unittest
from tictactoe import Board, HumanPlayer, AIPlayer # Assuming tictactoe.py is in the same directory

class TestBoard(unittest.TestCase):
    def setUp(self):
        self.board = Board()

    def test_board_init(self):
        # Test that the board is initialized correctly
        expected_board = [
            ['-', '-', '-'],
            ['-', '-', '-'],
            ['-', '-', '-'],
        ]
        self.assertEqual(self.board.board, expected_board)

    def test_board_str(self):
        # Test the string representation of the board
        expected_str = """-------------
| - | - | - |
-------------
| - | - | - |
-------------
| - | - | - |
-------------"""
        self.assertEqual(str(self.board), expected_str)

    def test_is_valid_move(self):
        # Test valid moves
        self.assertTrue(self.board.is_valid_move(0, 0))
        self.assertTrue(self.board.is_valid_move(1, 1))
        self.assertTrue(self.board.is_valid_move(2, 2))

        # Test invalid moves - out of bounds
        self.assertFalse(self.board.is_valid_move(-1, 0))
        self.assertFalse(self.board.is_valid_move(3, 0))
        self.assertFalse(self.board.is_valid_move(0, -1))
        self.assertFalse(self.board.is_valid_move(0, 3))

        # Test invalid moves - already occupied
        self.board.place_move(0, 0, 'X')
        self.assertFalse(self.board.is_valid_move(0, 0))

    def test_place_move(self):
        self.board.place_move(0, 0, 'X')
        self.assertEqual(self.board.board[0][0], 'X')
        self.board.place_move(1, 2, 'O')
        self.assertEqual(self.board.board[1][2], 'O')

    def test_check_win_rows(self):
        # Test X wins in a row
        self.board.place_move(0, 0, 'X')
        self.board.place_move(0, 1, 'X')
        self.board.place_move(0, 2, 'X')
        self.assertEqual(self.board.check_win(), 'X')

        self.setUp() # Reset board
        self.board.place_move(1, 0, 'O')
        self.board.place_move(1, 1, 'O')
        self.board.place_move(1, 2, 'O')
        self.assertEqual(self.board.check_win(), 'O')

    def test_check_win_columns(self):
        # Test X wins in a column
        self.board.place_move(0, 0, 'X')
        self.board.place_move(1, 0, 'X')
        self.board.place_move(2, 0, 'X')
        self.assertEqual(self.board.check_win(), 'X')

        self.setUp() # Reset board
        self.board.place_move(0, 1, 'O')
        self.board.place_move(1, 1, 'O')
        self.board.place_move(2, 1, 'O')
        self.assertEqual(self.board.check_win(), 'O')

    def test_check_win_diagonals(self):
        # Test X wins in main diagonal
        self.board.place_move(0, 0, 'X')
        self.board.place_move(1, 1, 'X')
        self.board.place_move(2, 2, 'X')
        self.assertEqual(self.board.check_win(), 'X')

        self.setUp() # Reset board
        # Test O wins in anti-diagonal
        self.board.place_move(0, 2, 'O')
        self.board.place_move(1, 1, 'O')
        self.board.place_move(2, 0, 'O')
        self.assertEqual(self.board.check_win(), 'O')

    def test_check_win_no_win(self):
        # Test no win condition
        self.board.place_move(0, 0, 'X')
        self.board.place_move(0, 1, 'O')
        self.board.place_move(0, 2, 'X')
        self.board.place_move(1, 0, 'O')
        self.board.place_move(1, 1, 'X')
        self.board.place_move(1, 2, 'O')
        self.board.place_move(2, 0, 'O')
        self.board.place_move(2, 1, 'X')
        self.assertEqual(self.board.check_win(), "")

    def test_board_full(self):
        # Test a full board
        self.board.board = [
            ['X', 'O', 'X'],
            ['O', 'X', 'O'],
            ['O', 'X', 'O'],
        ]
        self.assertTrue(self.board.board_full())

        # Test a not full board
        self.setUp() # Reset board
        self.assertFalse(self.board.board_full())
        self.board.place_move(0, 0, 'X')
        self.assertFalse(self.board.board_full())

# We will add tests for HumanPlayer and AIPlayer later, as they involve input/output and more complex logic.

if __name__ == '__main__':
    unittest.main()
