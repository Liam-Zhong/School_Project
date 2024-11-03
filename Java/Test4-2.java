import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] numbers = new int[10];
        System.out.println("Please input 10 numbers:");
        for (int i = 0; i < 10; i++) {
            numbers[i] = scanner.nextInt();
        }
        
        System.out.println("Your numbers are:");
        for (int i = 0; i < 10; i++) {
            System.out.print(numbers[i] + " ");
        }
        System.out.println();

        System.out.println("Please input m:");
        int m = scanner.nextInt();
        m = m % 10;
        
        System.out.println("The new numbers are:");
        for (int i = 0; i < 10; i++) {
            System.out.print(numbers[(10 - m + i) % 10] + " ");
        }
    }
}
