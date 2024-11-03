import java.util.Scanner;

public class hello {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please input a sentence: \n");
        String sentence = scanner.nextLine();

        int numLetters = 0;
        int numDigits = 0;
        int numSpaces = 0;
        int numOthers = 0;

        for (int i = 0; i < sentence.length(); i++) {
            char ch = sentence.charAt(i);
            if (Character.isLetter(ch)) {
                numLetters++;
            } else if (Character.isDigit(ch)) {
                numDigits++;
            } else if (Character.isWhitespace(ch)) {
                numSpaces++;
            } else {
                numOthers++;
            }
        }

        System.out.println("The number of numbers is: " + numDigits);
        System.out.println("The number of English letters is: " + numLetters);
        System.out.println("The number of blank space is: " + numSpaces);
        System.out.println("The number of other characters is: " + numOthers);
    }
}
