import java.util.Scanner;

// Main.java
public class Main {

    static class Board {
        char[][] board;

        public Board() {
            board = new char[3][3];
            initBoard();
        }

        private void initBoard() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    board[i][j] = '-';
                }
            }
        }

        public void printBoard() {
            System.out.println("-------------");
            for (int i = 0; i < 3; i++) {
                System.out.print("| ");
                for (int j = 0; j < 3; j++) {
                    System.out.print(board[i][j] + " | ");
                }
                System.out.println();
                System.out.println("-------------");
            }
        }

        public boolean isValidMove(int row, int col) {
            if (row < 0 || row >= 3 || col < 0 || col >= 3) {
                return false;
            }
            return board[row][col] == '-';
        }

        public void placeMove(int row, int col, char playerSymbol) {
            board[row][col] = playerSymbol;
        }

        public boolean checkWin() {
            // Check rows
            for (int i = 0; i < 3; i++) {
                if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                    return true;
                }
            }
            // Check columns
            for (int j = 0; j < 3; j++) {
                if (board[0][j] != '-' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                    return true;
                }
            }
            // Check diagonals
            if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
                return true;
            }
            if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
                return true;
            }
            return false;
        }

        public boolean isBoardFull() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '-') {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    interface Player {
        void makeMove(Board board, char playerSymbol);
    }

    static class HumanPlayer implements Player {
        private Scanner scanner;

        public HumanPlayer(Scanner scanner) {
            this.scanner = scanner;
        }

        @Override
        public void makeMove(Board board, char playerSymbol) {
            int row, col;
            while (true) {
                System.out.println("Player " + playerSymbol + ", enter your move (row and column, e.g., 1 2): ");
                row = scanner.nextInt() - 1; // Adjust for 0-based indexing
                col = scanner.nextInt() - 1; // Adjust for 0-based indexing

                if (board.isValidMove(row, col)) {
                    board.placeMove(row, col, playerSymbol);
                    break;
                } else {
                    System.out.println("Invalid move. Try again.");
                }
            }
        }
    }

    static class AIPlayer implements Player {
        private char aiPlayerSymbol;
        private char opponentSymbol;

        public AIPlayer(char aiPlayerSymbol, char opponentSymbol) {
            this.aiPlayerSymbol = aiPlayerSymbol;
            this.opponentSymbol = opponentSymbol;
        }

        @Override
        public void makeMove(Board board, char playerSymbol) {
            System.out.println("AI Player " + playerSymbol + " is thinking...");
            int[] bestMove = findBestMove(board);
            board.placeMove(bestMove[0], bestMove[1], playerSymbol);
        }

        private int[] findBestMove(Board board) {
            int bestVal = Integer.MIN_VALUE;
            int[] bestMove = {-1, -1};

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board.isValidMove(i, j)) {
                        // Make the move
                        board.placeMove(i, j, aiPlayerSymbol);

                        // Compute evaluation function for this move
                        int moveVal = minimax(board, 0, false);

                        // Undo the move
                        board.placeMove(i, j, '-');

                        // If the value of the current move is more than the best value, then update bestVal
                        if (moveVal > bestVal) {
                            bestVal = moveVal;
                            bestMove[0] = i;
                            bestMove[1] = j;
                        }
                    }
                }
            }
            return bestMove;
        }

        private int minimax(Board board, int depth, boolean isMaximizingPlayer) {
            int score = evaluate(board);

            // If Maximizer has won the game
            if (score == 10) return score;

            // If Minimizer has won the game
            if (score == -10) return score;

            // If there are no more moves and no winner then it's a tie
            if (board.isBoardFull()) return 0;

            // If this maximizer's move
            if (isMaximizingPlayer) {
                int best = Integer.MIN_VALUE;

                // Traverse all cells
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        // Check if cell is empty
                        if (board.isValidMove(i, j)) {
                            // Make the move
                            board.placeMove(i, j, aiPlayerSymbol);

                            // Call minimax recursively and choose the maximum value
                            best = Math.max(best, minimax(board, depth + 1, !isMaximizingPlayer));

                            // Undo the move
                            board.placeMove(i, j, '-');
                        }
                    }
                }
                return best;
            } else { // If this minimizer's move
                int best = Integer.MAX_VALUE;

                // Traverse all cells
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        // Check if cell is empty
                        if (board.isValidMove(i, j)) {
                            // Make the move
                            board.placeMove(i, j, opponentSymbol);

                            // Call minimax recursively and choose the minimum value
                            best = Math.min(best, minimax(board, depth + 1, !isMaximizingPlayer));

                            // Undo the move
                            board.placeMove(i, j, '-');
                        }
                    }
                }
                return best;
            }
        }

        private int evaluate(Board board) {
            // Check for wins
            for (int row = 0; row < 3; row++) {
                if (board.board[row][0] == board.board[row][1] && board.board[row][1] == board.board[row][2]) {
                    if (board.board[row][0] == aiPlayerSymbol) return 10;
                    else if (board.board[row][0] == opponentSymbol) return -10;
                }
            }

            for (int col = 0; col < 3; col++) {
                if (board.board[0][col] == board.board[1][col] && board.board[1][col] == board.board[2][col]) {
                    if (board.board[0][col] == aiPlayerSymbol) return 10;
                    else if (board.board[0][col] == opponentSymbol) return -10;
                }
            }

            if (board.board[0][0] == board.board[1][1] && board.board[1][1] == board.board[2][2]) {
                if (board.board[0][0] == aiPlayerSymbol) return 10;
                else if (board.board[0][0] == opponentSymbol) return -10;
            }

            if (board.board[0][2] == board.board[1][1] && board.board[1][1] == board.board[2][0]) {
                if (board.board[0][2] == aiPlayerSymbol) return 10;
                else if (board.board[0][2] == opponentSymbol) return -10;
            }
            
            return 0; // No winner
        }
    }

    public static void main(String[] args) {
        System.out.println("Hello, Tic-Tac-Toe!");
        Scanner scanner = new Scanner(System.in);
        Board board = new Board();
        Player player1 = new HumanPlayer(scanner);
        Player player2;

        System.out.println("Choose opponent: (1) Human or (2) AI");
        int opponentChoice = scanner.nextInt();

        if (opponentChoice == 1) {
            player2 = new HumanPlayer(scanner);
        } else {
            player2 = new AIPlayer('O', 'X'); // AI plays as 'O', human as 'X'
        }

        char currentPlayerSymbol = 'X';
        Player currentPlayer = player1;

        while (true) {
            board.printBoard();
            currentPlayer.makeMove(board, currentPlayerSymbol);

            if (board.checkWin()) {
                board.printBoard();
                System.out.println("Player " + currentPlayerSymbol + " wins!");
                break;
            }
            if (board.isBoardFull()) {
                board.printBoard();
                System.out.println("It's a draw!");
                break;
            }

            // Switch players
            if (currentPlayerSymbol == 'X') {
                currentPlayerSymbol = 'O';
                currentPlayer = player2;
            } else {
                currentPlayerSymbol = 'X';
                currentPlayer = player1;
            }
        }
        scanner.close();
    }
}
