package BaiTH2;

import java.util.Scanner;

public class SDDate {
	public static void main(String[] args) {
		Date d1 = new Date();
		System.out.print("Ham xay dung mac nhien: ");
		d1.hienThi();
		System.out.println();
		
		Date d2 = new Date(31,12,2024);
		System.out.print("Ham xay dung co chua doi so: ");
		d2.hienThi();
		System.out.println();
		
		Date d3 = new Date(31,6,2000);
		if (d3.hopLe()) {
			d3.hienThi();
			System.out.println(" la ngay hop le!!");
		}
		else {
			d3.hienThi();
			System.out.println(" khong phai la ngay hop le!!");
		}
		
		Date d4 = new Date(29,2,1999);
		if (d4.hopLe()) {
			d4.hienThi();
			System.out.println(" la ngay hop le!!");
		}
		else {
			d4.hienThi();
			System.out.println(" khong phai la ngay hop le!!");
		}
		
		Scanner sc = new Scanner(System.in);
		Date d5 = new Date();
		System.out.println("Nhap ngay/thang/nam: ");
		d5.nhap(sc);
		System.out.println("Sau khi nhap: ");
		d5.hienThi();
		System.out.println();
		
		
		Date d6 = new Date(30,6,2007);
		System.out.print("Ngay hom sau cua ");
		d6.hienThi();
		System.out.print(" la: ");
		d6.ngayHomSau().hienThi();
		System.out.println();
		

		Date d7 = new Date(15,6,2000);
		System.out.print("d7 sau 20 ngay la: ");
		d7.congNgay(20).hienThi();
	}
}
