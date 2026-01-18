import pytest
from tictactoe import Board

@pytest.fixture
def board():
    return Board()

def test_board_init(board):
    expected_board = [
        ['-', '-', '-'],
        ['-', '-', '-'],
        ['-', '-', '-'],
    ]
    assert board.board == expected_board

def test_board_str(board):
    expected_str = """-------------
| - | - | - |
-------------
| - | - | - |
-------------
| - | - | - |
-------------"""
    assert str(board) == expected_str

def test_is_valid_move(board):
    # Test valid moves
    assert board.is_valid_move(0, 0)
    assert board.is_valid_move(1, 1)
    assert board.is_valid_move(2, 2)

    # Test invalid moves - out of bounds
    assert not board.is_valid_move(-1, 0)
    assert not board.is_valid_move(3, 0)
    assert not board.is_valid_move(0, -1)
    assert not board.is_valid_move(0, 3)

    # Test invalid moves - already occupied
    board.place_move(0, 0, 'X')
    assert not board.is_valid_move(0, 0)

def test_place_move(board):
    board.place_move(0, 0, 'X')
    assert board.board[0][0] == 'X'
    board.place_move(1, 2, 'O')
    assert board.board[1][2] == 'O'

def test_check_win_rows(board):
    # Test X wins in a row
    board.place_move(0, 0, 'X')
    board.place_move(0, 1, 'X')
    board.place_move(0, 2, 'X')
    assert board.check_win() == 'X'

    board = Board() # Reset board
    board.place_move(1, 0, 'O')
    board.place_move(1, 1, 'O')
    board.place_move(1, 2, 'O')
    assert board.check_win() == 'O'

def test_check_win_columns(board):
    # Test X wins in a column
    board.place_move(0, 0, 'X')
    board.place_move(1, 0, 'X')
    board.place_move(2, 0, 'X')
    assert board.check_win() == 'X'

    board = Board() # Reset board
    board.place_move(0, 1, 'O')
    board.place_move(1, 1, 'O')
    board.place_move(2, 1, 'O')
    assert board.check_win() == 'O'

def test_check_win_diagonals(board):
    # Test X wins in main diagonal
    board.place_move(0, 0, 'X')
    board.place_move(1, 1, 'X')
    board.place_move(2, 2, 'X')
    assert board.check_win() == 'X'

    board = Board() # Reset board
    # Test O wins in anti-diagonal
    board.place_move(0, 2, 'O')
    board.place_move(1, 1, 'O')
    board.place_move(2, 0, 'O')
    assert board.check_win() == 'O'

def test_check_win_no_win(board):
    # Test no win condition
    board.place_move(0, 0, 'X')
    board.place_move(0, 1, 'O')
    board.place_move(0, 2, 'X')
    board.place_move(1, 0, 'O')
    board.place_move(1, 1, 'X')
    board.place_move(1, 2, 'O')
    board.place_move(2, 0, 'O')
    board.place_move(2, 1, 'X')
    board.place_move(2, 2, 'O')
    assert board.check_win() == ""

def test_board_full(board):
    # Test a full board
    board.board = [
        ['X', 'O', 'X'],
        ['O', 'X', 'O'],
        ['O', 'X', 'O'],
    ]
    assert board.board_full()

    # Test a not full board
    board = Board() # Reset board
    assert not board.board_full()
    board.place_move(0, 0, 'X')
    assert not board.board_full()
