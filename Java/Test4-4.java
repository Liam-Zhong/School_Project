import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        int n = scanner.nextInt();
        System.out.println(getMinNumber(s, n));
    }

    public static String getMinNumber(String s, int n) {
        StringBuilder result = new StringBuilder();
        int length = s.length();
        int keep = length - n;
        int start = 0;

        for (int i = 0; i < keep; i++) {
            char minChar = '9' + 1;
            int minIndex = start;

            for (int j = start; j <= n + i; j++) {
                if (s.charAt(j) < minChar) {
                    minChar = s.charAt(j);
                    minIndex = j;
                }
            }

            result.append(minChar);
            start = minIndex + 1;
        }

        while (result.length() > 1 && result.charAt(0) == '0') {
            result.deleteCharAt(0);
        }

        return result.toString();
    }
}
