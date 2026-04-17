package buoi1;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Tong2SoNguyen {
	public static void nhapSoNguyen() {
		Scanner sc = new Scanner(System.in);
		int a, b;
		while (true) {
			try {
				System.out.println("Nhap 2 so nguyen a, b: ");
				a = sc.nextInt();
				b = sc.nextInt();
				break;
			}
			catch(InputMismatchException e) {
				System.out.println("Nhap sai dinh dang!");
				sc.nextLine();
			}
		}
		sc.close();
		System.out.println((a+b));
	}
	
	public static void main(String[] args) {
		nhapSoNguyen();
	}

}
