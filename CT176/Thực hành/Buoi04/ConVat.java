package BaiTH4;

import java.util.Scanner;

public abstract class ConVat {
	private String giong, mauLong;
	private float canNang;
	public ConVat() {
		giong = new String();
		mauLong = new String();
		canNang = 0.0f;
	}
	public ConVat(ConVat k) {
		this.giong = k.giong;
		this.mauLong = k.mauLong;
		this.canNang = k.canNang;
	}
	public abstract void Keu();
	
	public void nhap() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap ten giong: ");
		giong = sc.nextLine();
		System.out.println("Nhap mau long: ");
		mauLong = sc.nextLine();
		System.out.println("Nhap can nang: ");
		canNang = sc.nextFloat();
	}
	
	public String toString() {
		return "ConVat [giong=" + giong + ", mauLong=" + mauLong + ", canNang=" + canNang + "]";
	}
}
