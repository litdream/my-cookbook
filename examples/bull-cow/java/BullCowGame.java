import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;

public class BullCowGame {

    private List<Integer> secretNumber;

    public BullCowGame() {
        this.secretNumber = generateNumber();
    }

    private List<Integer> generateNumber() {
        Random random = new Random();
        List<Integer> number = new ArrayList<>();
        Set<Integer> uniqueDigits = new HashSet<>();

        while (number.size() < 3) {
            int digit = random.nextInt(9) + 1; // Digits from 1 to 9
            if (uniqueDigits.add(digit)) {
                number.add(digit);
            }
        }
        return number;
    }

    public List<Integer> getSecretNumber() {
        return secretNumber;
    }

    public int[] match(String userInput) {
        int bulls = 0;
        int cows = 0;

        List<Integer> userGuess = new ArrayList<>();
        for (char c : userInput.toCharArray()) {
            userGuess.add(Character.getNumericValue(c));
        }

        // Calculate bulls
        for (int i = 0; i < 3; i++) {
            if (userGuess.get(i).equals(secretNumber.get(i))) {
                bulls++;
            }
        }

        // Calculate cows
        for (int i = 0; i < 3; i++) {
            if (secretNumber.contains(userGuess.get(i)) && !userGuess.get(i).equals(secretNumber.get(i))) {
                cows++;
            }
        }

        return new int[]{bulls, cows};
    }
}
