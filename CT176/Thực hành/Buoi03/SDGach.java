package BaiTH3;

import java.util.Scanner;

public class SDGach {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Gach G = new Gach();
		System.out.println("Nhap thong tin loai gach");
		G.nhap(sc);
		System.out.println("Thong tin loai gach");
		G.hienThi();
		int n=0;
		System.out.println("So luong hop gach ban muon nhap? ");
		n= sc.nextInt();
		sc.nextLine();
		Gach[] ds= new Gach[n];
		System.out.println("Nhap danh sach hop gach ");
		for(int i=0; i<n ; i++) {
			System.out.println("Nhap hop gach thu " +(i+1));
			ds[i]= new Gach();
			ds[i].nhap(sc);
			sc.nextLine();
		}
		System.out.println();
		for(Gach g: ds) {
			g.hienThi();
			System.out.println();
		}
	}
}
