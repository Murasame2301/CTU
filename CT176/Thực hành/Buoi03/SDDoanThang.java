package BaiTH3;

import java.util.Scanner;

import BaiTH2.Diem;


public class SDDoanThang {
	public static void main(String[] args) {
		Diem A = new Diem(2, 5);
		Diem B = new Diem(20, 35);
		DoanThang AB = new DoanThang(A,B);
		AB = AB.tinhTien(5, 3);
		Scanner sc = new Scanner(System.in);
		DoanThang CD = new DoanThang();
		CD.nhap(sc);
		System.out.print("Do dai cua doan CD la: ");
		System.out.printf(" %.2f", CD.doDai());
		
	}
}
