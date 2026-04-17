package BaiTH2;

import java.util.Scanner;

public class SDDiem {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Diem A = new Diem(3,4); 
		System.out.print("Toa do diem A la: ");
		A.hienThi();
		System.out.println();
		
		Diem B = new Diem(); 
		System.out.print("Nhap toa do diem B: ");
		B.nhapDiem(sc);
		System.out.print("Toa do diem B la: ");
		B.hienThi();
		
		System.out.println();
		Diem C = new Diem(); 
		C.setX(-B.giaTriX()); C.setY(-B.giaTriY()); 
		System.out.print("Toa do diem C la: ");
		C.hienThi();
		System.out.println();
		
		System.out.printf("Khoang cach OA = %.2f\n", B.khoangCach());
		
		System.out.printf("Khoang cach AB = %.2f\n", A.khoangCach(B));
	}

}
