package test;

import java.util.Scanner;

public class Hello {
    
    public static boolean isPerfectNumber(int num) {
        if (num <= 1) return false;
        int sum = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                sum += i;
                if (i * i != num) {
                    sum += num / i;
                }
            }
        }
        return sum == num;
    }
    
    public static String findPerfectNumbers(int start, int end) {
        StringBuilder result = new StringBuilder();
        for (int i = start; i <= end; i++) {
            if (isPerfectNumber(i)) {
                if (result.length() > 0) result.append(",");
                result.append(i);
            }
        }
        return result.toString();
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int m = in.nextInt();
        int n = in.nextInt();
        
        String perfectNumbers = findPerfectNumbers(m, n);
        System.out.printf("%d to %d WanShu:%n%s,", m, n, perfectNumbers);
        
        in.close();
    }
}



