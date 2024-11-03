package test;

import java.util.Scanner;

public class test {
	public static void main (String[]args) {
		Scanner in = new Scanner(System.in);
		int temple;
		int number;
		int result = 0;
		number = in.nextInt();
		for(temple = 1;temple <= number;temple ++)
		{
			result += jiecheng(temple) ;
		}
		System.out.println("1!~" + number + "!=" + result
				);
	}



public static long jiecheng (int number) {
	long result =1;
	for(int i=1;i<=number;i++) {
		result *=i;
	}
	return result;
}
}

