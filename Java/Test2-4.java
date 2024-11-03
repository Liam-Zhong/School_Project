import java.util.Scanner;

public class hello {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int number = in.nextInt();

        if (isReversiblePrime(number)) {
            System.out.println("yes");
        } else {
            System.out.println("no");
        }
    }

    public static boolean isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    public static boolean isReversiblePrime(int n) {
        if (!isPrime(n)) {
            return false;
        }
 
        int reversedNumber = reverseNumber(n);
       
        return isPrime(reversedNumber);
    }

    public static int reverseNumber(int n) {
        int reversed = 0;
        while (n > 0) {
            reversed = reversed * 10 + n % 10;
            n /= 10;
        }
        return reversed;
    }
}

