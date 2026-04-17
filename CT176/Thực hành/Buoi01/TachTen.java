package buoi1;

import java.util.Scanner;

public class TachTen {

	public static String get_Name(String fullname){
		String name = new String(fullname);
		name = name.trim();
		return name.substring(name.lastIndexOf(" ")+1);
	}
	public static void main(String[] args){		
		Scanner sc  = new Scanner(System.in);
		System.out.print("\nNhap ho va ten: ");
		String fullname = sc.nextLine();
		sc.close();
		System.out.println("Ho va ten: "+ fullname);
		System.out.println("Ten da tach: " + get_Name(fullname));
		
	}
}
