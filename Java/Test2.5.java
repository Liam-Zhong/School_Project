import java.util.Scanner;

public class hello {
    public static void main(String[] args) {
     
        Scanner in = new Scanner(System.in);
      
        System.out.println("Please input the first number:");
        int a = in.nextInt();
        
        System.out.println("Please input the second number:");
        int b = in.nextInt();
       
        System.out.println("Please input the third number:");
        int c = in.nextInt();
        
        int max = findMax(a, b, c);
 
        System.out.println("The maximum number is:" + max);

    }

    public static int findMax(int a, int b, int c) {
        int max = a;
        if (b > max) {
            max = b;
        }
        if (c > max) {
            max = c;
        }
        return max;
    }
}

