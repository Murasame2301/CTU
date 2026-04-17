package BaiTH5;

import java.util.Scanner;

public class KhachHang {
	private String cccd, hten, dchi;
	
	public KhachHang() {
		cccd = new String();
		hten = new String();
		dchi = new String();
	}
	
	public KhachHang(String cccd, String hten, String dchi) {
		super();
		this.cccd = cccd;
		this.hten = hten;
		this.dchi = dchi;
	}



	public KhachHang(KhachHang kh) {
		cccd = kh.cccd;
		hten = kh.hten;
		dchi = kh.dchi;
	}

	public void nhap() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap cccd: ");
		cccd = sc.nextLine();
		System.out.println("Nhap ho ten: ");
		hten = sc.nextLine();
		System.out.println("Nhap dia chi: ");
		dchi = sc.nextLine();
	}
	
	public String toString() {
		return "CCCD: " + cccd + "\nHo ten: " + hten + "\nDia chi: " + dchi;
}
	public void in() {
		System.out.println(this);
	}
	
	public static void main(String[] args) {
		KhachHang x = new KhachHang();
		x.nhap();
		x.in();
	}
	public float getTLeGiam() {
		return 0;
	}
}
