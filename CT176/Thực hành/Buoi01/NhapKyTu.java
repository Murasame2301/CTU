package buoi1;

import java.util.Scanner;

public class NhapKyTu {
		public static void nhapKyTu() {
			Scanner sc = new Scanner(System.in);
			char ch;
			do {
				System.out.println("Nhap 1 ky tu: ");
				ch = sc.nextLine().charAt(0);
				System.out.println("Ky tu vua nhap: "+ ch);
			} while (ch!='q');
			sc.close();
	}
	public static void main(String[] args) {
		nhapKyTu();
	}
}
