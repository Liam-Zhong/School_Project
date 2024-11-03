import java.util.Scanner;

public class hello {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("Please input a number:");
        int n = in.nextInt();

        int sum = 0;
        StringBuilder expression = new StringBuilder("1"); // Initialize expression with "1"

        // Calculate the sum of factorials and build the expression
        for (int i = 2; i <= n; i++) {
            sum += factorial(i);
            if (i == 2) {
                expression.append("+2!"); // Add "2!" for the first iteration
            } else if (i == 3) {
                expression.append("+3!"); // Add "3!" for the second iteration
            } else if (i == n) {
                expression.append("+...+").append("n!"); // Add "...+n!" for the last iteration
            }
        }

        sum += factorial(1); // Add 1! to the total sum

        // Print the complete expression with the sum
        System.out.println(expression + "= " + sum);

        in.close();
    }

    // Method to calculate factorial
    public static int factorial(int num) {
        int result = 1;
        for (int i = 1; i <= num; i++) {
            result *= i;
        }
        return result;
    }
}
