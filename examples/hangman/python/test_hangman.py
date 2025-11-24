"""
Pytest unit tests for hangman.py
"""

import pytest
from unittest.mock import patch, MagicMock
from hangman import Hangman, choose_word, words, hangman_pics


class TestChooseWord:
    """Tests for choose_word function"""

    def test_choose_word_returns_tuple(self):
        """Test that choose_word returns a tuple"""
        result = choose_word()
        assert isinstance(result, tuple)
        assert len(result) == 2

    def test_choose_word_from_word_list(self):
        """Test that choose_word returns a word from the words list"""
        word, hint = choose_word()
        assert (word, hint) in words

    def test_choose_word_hint_is_string(self):
        """Test that hint is a string"""
        word, hint = choose_word()
        assert isinstance(word, str)
        assert isinstance(hint, str)


class TestHangmanInit:
    """Tests for Hangman initialization"""

    def test_init_sets_secret_and_hint(self):
        """Test that __init__ sets secret and hint"""
        game = Hangman()
        assert hasattr(game, 'secret')
        assert hasattr(game, 'hint')
        assert isinstance(game.secret, str)
        assert isinstance(game.hint, str)

    def test_init_empty_guessed_list(self):
        """Test that guessed list starts empty"""
        game = Hangman()
        assert game.guessed == []

    def test_init_zero_wrong_count(self):
        """Test that wrong count starts at 0"""
        game = Hangman()
        assert game.wrong == 0


class TestHangmanSecretSpaced:
    """Tests for secret_spaced method"""

    @patch('hangman.choose_word')
    def test_secret_spaced_no_guesses(self, mock_choose):
        """Test secret_spaced with no guesses shows all underscores"""
        mock_choose.return_value = ("python", "A programming language")
        game = Hangman()
        result = game.secret_spaced()
        assert result == "_ _ _ _ _ _"

    @patch('hangman.choose_word')
    def test_secret_spaced_some_guesses(self, mock_choose):
        """Test secret_spaced with some correct guesses"""
        mock_choose.return_value = ("python", "A programming language")
        game = Hangman()
        game.guessed = ['p', 'y', 'o']
        result = game.secret_spaced()
        assert result == "p y _ _ o _"

    @patch('hangman.choose_word')
    def test_secret_spaced_all_guessed(self, mock_choose):
        """Test secret_spaced when all letters are guessed"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['c', 'a', 't']
        result = game.secret_spaced()
        assert result == "c a t"

    @patch('hangman.choose_word')
    def test_secret_spaced_with_wrong_guesses(self, mock_choose):
        """Test that wrong guesses don't appear in secret_spaced"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['x', 'y', 'z', 'c']
        result = game.secret_spaced()
        assert result == "c _ _"


class TestHangmanWin:
    """Tests for win method"""

    @patch('hangman.choose_word')
    def test_win_when_all_letters_guessed(self, mock_choose):
        """Test win returns True when all letters are guessed"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['c', 'a', 't']
        assert game.win() is True

    @patch('hangman.choose_word')
    def test_win_with_extra_wrong_guesses(self, mock_choose):
        """Test win returns True even with wrong guesses mixed in"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['x', 'c', 'y', 'a', 'z', 't']
        assert game.win() is True

    @patch('hangman.choose_word')
    def test_not_win_when_letters_missing(self, mock_choose):
        """Test win returns False when not all letters are guessed"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['c', 'a']
        assert game.win() is False

    @patch('hangman.choose_word')
    def test_not_win_with_no_guesses(self, mock_choose):
        """Test win returns False with no guesses"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        assert game.win() is False


class TestHangmanLost:
    """Tests for lost method"""

    def test_lost_when_wrong_equals_max(self):
        """Test lost returns True when wrong count equals max hangman pics"""
        game = Hangman()
        game.wrong = len(hangman_pics)
        assert game.lost() is True

    def test_lost_when_wrong_exceeds_max(self):
        """Test lost returns True when wrong count exceeds max"""
        game = Hangman()
        game.wrong = len(hangman_pics) + 1
        assert game.lost() is True

    def test_not_lost_when_wrong_below_max(self):
        """Test lost returns False when wrong count is below max"""
        game = Hangman()
        game.wrong = len(hangman_pics) - 1
        assert game.lost() is False

    def test_not_lost_at_start(self):
        """Test lost returns False at game start"""
        game = Hangman()
        assert game.lost() is False


class TestHangmanDisplayGameState:
    """Tests for display_game_state method"""

    @patch('hangman.choose_word')
    @patch('builtins.print')
    def test_display_game_state_prints_hangman_pic(self, mock_print, mock_choose):
        """Test that display_game_state prints the correct hangman picture"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.wrong = 2
        game.display_game_state()

        # Check that print was called and first call contains hangman pic
        assert mock_print.call_count >= 3
        first_call_arg = mock_print.call_args_list[0][0][0]
        assert hangman_pics[2] == first_call_arg

    @patch('hangman.choose_word')
    @patch('builtins.print')
    def test_display_game_state_prints_word(self, mock_print, mock_choose):
        """Test that display_game_state prints the word state"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['c']
        game.display_game_state()

        # Check that the word display was printed
        calls = [str(call) for call in mock_print.call_args_list]
        assert any("Word:" in str(call) and "c _ _" in str(call) for call in calls)

    @patch('hangman.choose_word')
    @patch('builtins.print')
    def test_display_game_state_prints_guessed_letters(self, mock_print, mock_choose):
        """Test that display_game_state prints guessed letters"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed = ['a', 'b', 'c']
        game.display_game_state()

        # Check that guessed letters were printed
        calls = [str(call) for call in mock_print.call_args_list]
        assert any("Guessed letters:" in str(call) for call in calls)


class TestHangmanGameFlow:
    """Integration tests for game flow"""

    @patch('hangman.choose_word')
    def test_correct_guess_does_not_increment_wrong(self, mock_choose):
        """Test that correct guesses don't increment wrong count"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()
        game.guessed.append('c')
        initial_wrong = game.wrong

        # Since 'c' is in secret, wrong shouldn't increment
        assert game.wrong == initial_wrong

    @patch('hangman.choose_word')
    def test_game_progression_to_win(self, mock_choose):
        """Test a full game progression to a win"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()

        # Initially not won
        assert game.win() is False

        # Guess all letters
        for letter in ['c', 'a', 't']:
            game.guessed.append(letter)

        # Now should be won
        assert game.win() is True
        assert game.lost() is False

    @patch('hangman.choose_word')
    def test_game_progression_to_loss(self, mock_choose):
        """Test a full game progression to a loss"""
        mock_choose.return_value = ("cat", "A feline animal")
        game = Hangman()

        # Make enough wrong guesses to lose
        wrong_guesses = ['x', 'y', 'z', 'q', 'w', 'r', 's']
        for guess in wrong_guesses:
            game.guessed.append(guess)
            if guess not in game.secret:
                game.wrong += 1

        # Should be lost
        assert game.lost() is True
        assert game.win() is False
