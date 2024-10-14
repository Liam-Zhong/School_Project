package test;

import java.util.Scanner;

public class test {
	public static void main (String[]args) {
		Scanner in = new Scanner(System.in);
		double y = 0;
		double n = in.nextDouble();
		if (n>0) {
			y=Math.exp(-n);
			System.out.printf("y=" + String.format("%.4f", y));
		}
		else if (n < 0) {
			y=-Math.exp(n);
			System.out.printf("y=" + String.format("%.4f", y));
		}
		else {
			y=1;
			System.out.printf("y=" + String.format("%.4f", y));
		}
//		for(temple = 1;temple <= number;temple ++)
//		{
//			result += jiecheng(temple) ;
//		}
//		System.out.printf("y=" + String.format("%.4f", y));
	}
}
