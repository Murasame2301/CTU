package BaiTH5;

import java.util.Scanner;

public class KhachHangVIP extends KhachHang {
	private float tLeGiam;
	private Date ngayLenVIP;
	
	public KhachHangVIP() {
		tLeGiam = 0.0f;
		ngayLenVIP = new Date();
	}


	public KhachHangVIP(String cccd, String hten, String dchi, float tLeGiam, Date ngayLenVIP) {
		super(cccd, hten, dchi);
		this.tLeGiam = tLeGiam;
		this.ngayLenVIP = ngayLenVIP;
	}


	public KhachHangVIP(KhachHangVIP kh) {
		super(kh);
		this.tLeGiam = kh.tLeGiam;
		this.ngayLenVIP = kh.ngayLenVIP;
	}


	public void nhap() {
		Scanner sc = new Scanner(System.in);
		super.nhap();
		System.out.println("Nhap vao ngay tro thanh khach hang VIP: ");
		ngayLenVIP.nhap(sc);
		System.out.println("Nhap ti le giam: ");
		tLeGiam = sc.nextFloat();
}
	

	public void in() {
		System.out.println(this);
		System.out.print("Ngay len VIP: ");
		ngayLenVIP.hienThi();
		System.out.printf("\nTi le giam: %.2f %", tLeGiam);
	}
	
	public float getTLeGiam() {
		return tLeGiam;
	}
}
