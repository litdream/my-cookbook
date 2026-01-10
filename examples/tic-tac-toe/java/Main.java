import java.util.Scanner;

class Player {
    private String mark;

    public Player(String mark) {
        this.mark = mark;
    }

    public String getMark() {
        return mark;
    }
}

class Board {
    private String[][] board = {
        {"-", "-", "-"},
        {"-", "-", "-"},
        {"-", "-", "-"}
    };

    public void printBoard() {
        for (String[] row : board) {
            for (String cell : row) {
                System.out.print(cell + " ");
            }
            System.out.println();
        }
    }

    public boolean makeMove(int row, int col, String mark) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col].equals("-")) {
            board[row][col] = mark;
            return true;
        }
        return false;
    }

    public String getPos(int r, int c) {
        return board[r][c];
    }
}

class Game {
    private Player p1, p2;
    private Board board;

    public Game(Board b, Player p1, Player p2) {
        this.board = b;
        this.p1 = p1;
        this.p2 = p2;
    }

    public Player checkWin() {
        for (int i = 0; i < 3; i++) {
            // Rows & Columns
            if (isEqual(board.getPos(i,0), board.getPos(i,1), board.getPos(i,2))) return getWinner(board.getPos(i,0));
            if (isEqual(board.getPos(0,i), board.getPos(1,i), board.getPos(2,i))) return getWinner(board.getPos(0,i));
        }
        // Diagonals
        if (isEqual(board.getPos(0,0), board.getPos(1,1), board.getPos(2,2))) return getWinner(board.getPos(0,0));
        if (isEqual(board.getPos(0,2), board.getPos(1,1), board.getPos(2,0))) return getWinner(board.getPos(0,2));

        return null;
    }

    private boolean isEqual(String s1, String s2, String s3) {
        return !s1.equals("-") && s1.equals(s2) && s2.equals(s3);
    }

    private Player getWinner(String mark) {
        return mark.equals(p1.getMark()) ? p1 : p2;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Player p1 = new Player("O"), p2 = new Player("X");
        Board b = new Board();
        Game game = new Game(b, p1, p2);

        Player current = p1;
        int rounds = 0;

        while (rounds < 9 && game.checkWin() == null) {
            b.printBoard();
            System.out.print("Player " + current.getMark() + " (row col): ");
            if (b.makeMove(scanner.nextInt(), scanner.nextInt(), current.getMark())) {
                current = (current == p1) ? p2 : p1;
                rounds++;
            } else {
                System.out.println("Invalid move!");
            }
        }

        b.printBoard();
        Player win = game.checkWin();
        System.out.println(win != null ? "Winner: " + win.getMark() : "Draw!");
        scanner.close();
    }
}
