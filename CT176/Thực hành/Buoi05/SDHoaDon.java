package BaiTH5;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class SDHoaDon {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap so luong hoa don: ");
		int n = sc.nextInt();
		HoaDon[] ds = new HoaDon[n];
		for (int i = 0; i < n; i++) {
			System.err.println("\nNhap hoa don thu " + (i + 1));
			ds[i] = new HoaDon();
			ds[i].nhap();
		}
		System.err.println("\nNhung hoa don tren 1tr dong la: ");
		for (HoaDon x: ds) {
			if (x == null) break;
			if (x.tong() > 1000000) x.in();
		}
		
		HashMap<String,ArrayList<HoaDon>> hoaDonTheoNgay = new HashMap<>();
		for (HoaDon hd: ds) {
			if (hd == null) break;
			String NgLap = hd.getNglap().toString();
			if (!hoaDonTheoNgay.containsKey(NgLap)) {
				hoaDonTheoNgay.put(NgLap, new ArrayList<>());
			}
			hoaDonTheoNgay.get(NgLap).add(hd);
		}
		
		System.err.println("\n\nNhung hoa don duoc phat hanh vao 20/5/2022 la: ");
		for (HoaDon hd: hoaDonTheoNgay.get("20/5/2022")) {
			hd.in();
		}
	}
}
