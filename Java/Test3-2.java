import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n;

        while (true) {
            n = in.nextInt();

            if (n == 0) {
                System.out.println("programe is over.");
                break;
            }

            if (isPrime(n)) {
                System.out.println(n + " is sushu.");
            } else {
                System.out.println(n + " is not sushu.");
            }
        }

        in.close();
    }

    public static boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                return false;
            }
        }

        return true;
    }
}
