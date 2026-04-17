package BaiTH3;

import java.util.Arrays;
import java.util.Scanner;

public class SDSinhVien {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		SinhVien a = new SinhVien();
		a.nhap(sc);
		a.nhapDiem(sc);
		a.dangKihp("LTHDT");
		System.out.println(a.toString());
		System.out.println("Nhap danh sach sinh vien:\nNhap so luong: ");
		int n = sc.nextInt();
		sc.nextLine();
		SinhVien[] ds = new SinhVien[n];
		for (int i = 0; i < n; i++) {
			ds[i]= new SinhVien();
			System.out.println("Nhập thông tin sinh viên thứ " + (i+1));
			ds[i].nhap(sc);
			ds[i].nhapDiem(sc);
		}
		
		System.out.println("Danh sách sinh viên bị cảnh báo học vụ: ");
		for(SinhVien sv: ds) {
			if(sv.diemTB()<1.0) System.out.println(sv.getMSSV() + " " + sv.getHoTen());;
		}
		SinhVien best = ds[0];
		for(SinhVien sv: ds) {
			if(sv.diemTB()>best.diemTB()) {
				best = sv;
			}
		}
		System.out.println("Sinh viên có điểm trung bình cao nhất: " + best.getMSSV() + " " + best.getHoTen());
		Arrays.sort(ds, (s1, s2)-> s1.getHoTen().compareTo(s2.getHoTen()));
		for(SinhVien sv: ds) {
			System.out.println(sv.toString());
		}
	}
}