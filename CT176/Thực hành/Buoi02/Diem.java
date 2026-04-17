package BaiTH2;

import java.util.Scanner;

public class Diem {
	private int x,y;
	
	//Hàm xây dựng mặc nhiên
	public Diem() {
		x = 0; y = 0;
	}
	
	//Hàm xây dựng có chứa tham số
	public Diem(int a, int b) {
		x = a; 
		y = b;
	}
	
	//Hàm sao chép copy Constructor
	public Diem(Diem k) {
		x = k.x;
		y = k.y;
	}
	
	//Hàm thiết lập giá trị x
	public void setX(int x) {
		this.x = x;
	}
	
	//Hàm thiết lập giá trị x
	public void setY(int y) {
		this.y = y;
	}
	
	//Hàm nhập toạ độ điểm
	public void nhapDiem(Scanner sc) {
		x = sc.nextInt();
		y = sc.nextInt();
	}
	
	//Hàm hiển thị toạ độ điểm
	public void hienThi() {
		System.out.print("(" + x + ", " + y + ")");
	}
	
	//Doi diem di do doi (dx, dy)
	public void doiDiem(int dx, int dy) {
		x += dx;
		y += dy;
	}
	
	//Lây ra giá trị hoành độ của điểm
	public int giaTriX() {
		return x;
	}
	
	//Lây ra giá trị tung đô của điểm
	public int giaTriY() {
		return y;
	}
	
	//Khoảng cách từ điêm đó đên gốc toạ đô
	float khoangCach() {
		return (float)Math.sqrt(x*x + y*y);
	}
	
	//Khoảng cách từ điểm đó đến điểm d
	float khoangCach(Diem d) {
		return (float)Math.sqrt((x - d.x) * (x - d.x) + (y - d.y) * (y - d.y));
	}
}
