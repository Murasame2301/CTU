package BaiTH5;

import java.util.Scanner;

public class Date {
	private int ngay, thang, nam;
	//Hàm xây dựng mặc nhiên
	public Date() {
		ngay = 1;
		thang = 1;
		nam = 1970;
	}
	
	//Hàm xây dựng có tham số
	public Date(int d, int m, int y) {
		ngay = d;
		thang = m;
		nam = y;
	}

	//Ham sao chep constructor
	public Date(Date d){
		ngay = d.ngay;
		thang = d.thang;
		nam = d.nam;
	}
	
	public int getNgay() {
		return ngay;
	}
	
	public void setNgay(int ngay) {
		this.ngay = ngay;
	}
	
	public int getThang() {
		return thang;
	}
	
	public void setThang(int thang) {
		this.thang = thang;
	}
	
	public int getNam() {
		return nam;
	}
	
	public void setNam(int nam) {
		this.nam = nam;
	}
	//Ham in Date
	public void hienThi() {
		System.out.print(ngay + "/" + thang + "/" + nam);
	}
	
	public String toString() {
		return ngay + "/" + thang + "/" + nam;
	}
	
	//Hàm kiểm tra năm nhuận
	public boolean leapYear(){
		if((nam % 400==0) || (nam %4==0 && nam %100!=0))
			return true;
		return false;
	}

	//Hàm kiểm tra ngày hợp lệ
	public boolean hopLe(){
		int arr[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		if(leapYear())
			arr[2] = 29;
		if (ngay < 1 || thang < 1 || thang > 12 || ngay > arr[thang])
			return false;
		else return true;
	}
	
	//Hàm nhập Ngày
	public void nhap(Scanner sc) {
		do {
			System.out.print("Nhap ngay: ");
			ngay = sc.nextInt();
			System.out.print("Nhap thang: ");
			thang = sc.nextInt();
			System.out.print("Nhap nam: ");
			nam = sc.nextInt();
			if (!hopLe()) System.out.println("Nhap sai dinh dang roi!! Nhap lai.");
		}
		while (!hopLe());
	}
}
