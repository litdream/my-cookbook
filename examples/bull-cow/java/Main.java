import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        BullCowGame game = new BullCowGame();
        Scanner scanner = new Scanner(System.in);
        List<Integer> secretNumber = game.getSecretNumber();

        for (int i = 1; i <= 10; i++) {
            System.out.print("Round " + i + ":  Enter your guess: ");
            String userInput = scanner.nextLine().trim();

            // TODO: validate user input (e.g., 3 digits, unique digits)
            if (!isValidInput(userInput)) {
                System.out.println("Invalid input. Please enter a 3-digit number with unique digits (1-9).");
                i--; // Decrement round counter to allow user to try again
                continue;
            }

            int[] result = game.match(userInput);
            int bulls = result[0];
            int cows = result[1];

            if (bulls == 3) {
                System.out.println("Great!   You got this in " + i + " rounds. : " + secretNumber);
                return;
            }

            System.out.println(bulls + " bulls, " + cows + " cows");
        }

        System.out.println("Sorry:  The number was " + secretNumber + ".");
        scanner.close();
    }

    private static boolean isValidInput(String input) {
        if (input.length() != 3) {
            return false;
        }
        Set<Integer> uniqueDigits = new HashSet<>();
        for (char c : input.toCharArray()) {
            if (!Character.isDigit(c)) {
                return false;
            }
            int digit = Character.getNumericValue(c);
            if (digit == 0 || !uniqueDigits.add(digit)) { // Digits from 1-9, unique
                return false;
            }
        }
        return true;
    }
}
