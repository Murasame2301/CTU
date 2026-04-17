package BaiTH2;

import java.util.Scanner;

public class SDPhanSo {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		PhanSo a = new PhanSo(3,7), b = new PhanSo (4,9);
		System.out.print("Phan so a la: "); a.hienThi();
		System.out.println();
		System.out.print("Phan so b la: "); b.hienThi();
		System.out.println();
		
		PhanSo x = new PhanSo();
		System.out.print("Nhap phan so x: ");
		x.nhapPhanSo(sc);
		System.out.print("Phan so x la: ");
		x.hienThi();
		System.out.println();
		PhanSo y = new PhanSo();
		System.out.print("Nhap phan so y: ");
		y.nhapPhanSo(sc);
		System.out.print("Phan so y la: ");
		y.hienThi();
		System.out.println();
		
		System.out.print("Phan so nghich dao cua x la: ");
		x.giaTriNghichDao().hienThi();
		System.out.println();
		
		PhanSo Tong = x.congPhanSo(y);
		System.out.print("Tong hai phan so x va y la: ");
		Tong.hienThi();
		System.out.println();
		
		System.out.print("Nhap ds cac phan so:\nNhap n: ");	
		int n = sc.nextInt();
		PhanSo S = new PhanSo(0,1);
		PhanSo max = new PhanSo(-1000,1);
		PhanSo[] ds = new PhanSo[n];
		for (int i = 0; i < n; i++) {
			System.out.println("Nhap phan so thu " + (i+1));
			ds[i] = new PhanSo();
			ds[i].nhapPhanSo(sc);
			S = S.congPhanSo(ds[i]);
			if (ds[i].lonHon(max)) max = ds[i];
		}
		
		System.out.print("Ket qua tong cua " + n + " phan so la: ");
		S.hienThi();
		System.out.println();
		System.out.print("Phan so lon nhat la: ");
		max.hienThi();
		System.out.println();
		PhanSo tmp = new PhanSo();
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - i - 1; j++) {
				if (ds[j].lonHon(ds[j+1])) {
					tmp = ds[j];
					ds[j] = ds[j+1];
					ds[j+1] = tmp;
				}
		}
		
		
		System.out.print("Ds sau khi duoc sap xep: ");
		for (int i = 0; i < n; i++) ds[i].hienThi();
	}
}
