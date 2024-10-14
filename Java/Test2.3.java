package test;

import java.util.Scanner;

public class Hello {
	public static void main (String[] ars) { 
	Scanner in = new Scanner(System.in);
	int numbers_1 = in.nextInt();
	int numbers_2 = in.nextInt();
	int numbers_3 = in.nextInt();
	float su = numbers_3+numbers_2+numbers_1;
	float av = su / 3;
	String new_av =String.format ("%.1f",av);
	System.out.println("sum="  + su);
	System.out.println("average="  + new_av);
	
}
}

