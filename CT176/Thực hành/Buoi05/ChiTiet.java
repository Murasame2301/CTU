package BaiTH5;

import java.util.Scanner;

public class ChiTiet {
	private int sluong;
	private float dgia;
	
	
	public ChiTiet() {
		sluong = 0;
		dgia = 0;
	}

	public ChiTiet(int sluong, float dgia) {
		this.sluong = sluong;
		this.dgia = dgia;
	}
	
	public ChiTiet(ChiTiet ct) {
		this.sluong = ct.sluong;
		this.dgia = ct.dgia;
	}

	public void nhap() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap so luong: ");
		sluong = sc.nextInt();
		System.out.println("Nhap don gia: ");
		dgia = sc.nextFloat();
	}
	
	public void in() {
		System.out.println("So luong: " + sluong);
		System.out.printf("Don gia: %.2f\n", dgia);
		System.out.printf("Thanh tien: %.2f\n",this.tong());
	}
	
	public float tong() {
		return sluong * dgia;
	}
}
