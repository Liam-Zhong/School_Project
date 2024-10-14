package test;
import java.util.Scanner;

public class Hello {
	public static void main (String[]args) {
		Scanner in = new Scanner(System.in);
//		System.out.println("This is your first, second, third, forth or fifth JAVA code?\r\n" + 
//				"");
		int year = in.nextInt();
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
			System.out.println(year + " is leap year");
		} else {
		System.out.println(year + " is not leap year");
		}
	}
}

