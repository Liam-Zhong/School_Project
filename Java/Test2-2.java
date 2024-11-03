package test;

import java.util.Scanner;

public class Hello {
	public static void main (String[] ars) { 
	Scanner in = new Scanner(System.in);
	String name = in.nextLine();
	
	String strUpper = name.toUpperCase();
	System.out.println("result:" + strUpper);
}
}

