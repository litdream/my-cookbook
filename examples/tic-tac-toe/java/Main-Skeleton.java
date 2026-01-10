import java.io.*;


class Player {
    private int num;

    public Player(int n) {
	num = n;
    }
}

class Board {
    private int[][] board = {
	{0,0,0},
	{0,0,0},
	{0,0,0}
    };

    public Board() {

    }
	
}

class Game {
    private Player p1;
    private Player p2;
    private Board board;

    public Game(Board b, Player p1, Player p2) {
	board = b;
	this.p1 = p1;
	this.p2 = p2;
    }

    public Player checkWin() {
	// Return p1 or p2 if either one wins.
	// Otherwise return null;
    }
}


public class Main {
    public static void main(String[] args) {
	Player p1 = new Player(1);
	Player p2 = new Player(2);
	Board b = new Board();

	Game game = new Game(b, p1, p2);

	// loop and check for win game;
	int round = 0;
	while ( round < 9 && game.checkWin() == null ) {

	    round++;
	}
	
    }
}

