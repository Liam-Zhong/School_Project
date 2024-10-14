package test;

import java.util.Scanner;

public class test {
	public static void main (String[]args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		n = n-1;
		for(int i=0;i<=n+1;i++) { //start wih 0 not 1 
			int num = 1;
			int space = Math.max(0, (n-i)*2);
			try {
				System.out.printf("%" + space + "s" ,"");
			} catch (Exception e ) {
				
			}
			for (int j=0;j<=i;j++) {
				System.out.format("%4d", num);
				num = num * (i-j) / (j+1);
			}
			System.out.println(); // enter
		}
	}
}

