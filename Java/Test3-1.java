
import java.util.Scanner;

public class hello {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        System.out.println("Please input a score:");

        int n = in.nextInt();

        in.close();
        
        if (n >= 90) {
            System.out.println("A");
        } else if (n >= 80) {
            System.out.println("B");
        } else if (n >= 70) {
            System.out.println("C");
        } else if (n >= 60) {
            System.out.println("D");
        } else {
            System.out.println("E");
        }
    }
}
