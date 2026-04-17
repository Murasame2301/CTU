package BaiTH4;

import BaiTH2.Diem;

public class SDDiemMau {
	public static void main(String[] args) {
		Diem A = new DiemMau(5,10,"Trang");
		System.out.println("- Diem A: ");
		A.hienThi();
		System.out.println();
		DiemMau B = new DiemMau();
		System.out.println("Nhap DiemMau B:");
		B.nhap();
		B.doiDiem(5, 10);
		System.out.println("- Diem B: ");
		B.hienThi();
		System.out.println();
		B.GanMau("Vang");
		System.out.println("Diem B sau khi gan mau moi la: ");
		System.out.println(B.getMau());
	}
}
