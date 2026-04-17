package BaiTH3;

import java.util.Scanner;

import BaiTH2.Diem;

public class DoanThang {
	private Diem d1,d2;
	
	public DoanThang() {
		d1 = new Diem();
		d2 = new Diem();
	}
	
	public DoanThang(Diem A, Diem B) {
		d1 = new Diem(A);
		d2 = new Diem(B);
	}
	
	public DoanThang (int ax, int ay, int bx, int by) {
		d1 = new Diem(ax, ay);
		d2 = new Diem(bx, by);
	}
	
	public void nhap(Scanner sc) {
		System.out.println("Nhap Diem: ");
		System.out.print("Nhap toa do d1: ");
		d1.nhapDiem(sc);
		System.out.print("Nhap toa do d2: ");
		d2.nhapDiem(sc);
	}
	
	public void hienThi() {
		System.out.println("Toa do 2 diem cua doan thang la: ");
		d1.hienThi();
		System.out.println();
		d2.hienThi();
	}
	
	public DoanThang tinhTien(int dx, int dy) {
		DoanThang T = new DoanThang(d1,d2);
		T.d1.doiDiem(dx, dy);
		T.d2.doiDiem(dx, dy);
		return T;
	}
	public float doDai() {
		return d1.khoangCach(d2);
	}
}
