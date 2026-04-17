package BaiTH4;

import java.util.Scanner;

public class SDConVat {
	public static void main(String[] args) {
		System.out.print("Nhap so luong con vat: ");
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		sc.nextLine();
		
		char ch;
		System.out.println("Nhap ds cac con vat: ");
		ConVat[] ds = new ConVat[n];
		for (int i = 0; i < n; i++) {
			System.out.println("Nhap con vat thu " + (i+1));
			System.out.println("Bo nhap 'b', Heo nhap 'h', De nhap 'd':");
			ch = sc.nextLine().charAt(0);
			if (ch == 'b') ds[i] = new Bo();
			else if (ch == 'h')
				ds[i] = new Heo();
			else
				ds[i] = new De();
			ds[i].nhap();
			System.out.println();
		}
		
		for (int i = 0; i < n; i++) {
			System.out.print("Con Thu " + (i + 1) + " keu ");
			ds[i].Keu();
			System.out.println();
		}
	}
}
