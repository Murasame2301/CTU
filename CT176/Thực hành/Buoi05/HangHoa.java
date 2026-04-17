package BaiTH5;

import java.util.Scanner;

public class HangHoa {
	private String mso, ten, nsxuat;

	
	public HangHoa() {
		mso = new String();
		ten = new String();
		nsxuat = new String();
	}

	public HangHoa(String mso, String ten, String nsxuat) {
		this.mso = mso;
		this.ten = ten;
		this.nsxuat = nsxuat;
	}
	
	public HangHoa(HangHoa h) {
		mso = h.mso;
		ten = h.ten;
		nsxuat = h.nsxuat;
	}
	
	public void nhap() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap ma so hang hoa: ");
		mso = sc.nextLine();
		System.out.println("Nhap ten hang hoa: ");
		ten = sc.nextLine();
		System.out.println("Nhap ngay san xuat: ");
		Date d = new Date();
		d.nhap(sc);
		nsxuat = new String(d.toString());
	}
	
	public String toString() {
		return "Ma so hang hoa: " + mso + "\nTen hang hoa: " + ten + "\nNgay San Xuat: " + nsxuat;
	}
}
