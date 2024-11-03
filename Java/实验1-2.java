package test;
import java.util.Scanner;

public class Hello {
	public static void main (String[]args) {
		Scanner in = new Scanner(System.in);
		System.out.println("This is your first, second, third, forth or fifth JAVA code?\r\n" + 
				"");
		String name = in.nextLine();
		System.out.println("This is my "+ name + " JAVA code!");
	}
}

