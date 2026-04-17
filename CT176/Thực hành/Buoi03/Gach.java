package BaiTH3;

import java.util.Scanner;

public class Gach {
	private String maSo,color;
	private int chieuDai, chieuNgang, sl;
	private long giaBan;
	
	public Gach() {
		maSo = new String();
		color = new String();
		sl = chieuDai = chieuNgang = 0;
		giaBan = 0;
	}
	
	public Gach(Gach k) {
		maSo = new String(k.maSo);
		color = new String(k.color);
		sl = k.sl;
		chieuDai = k.chieuDai;
		chieuNgang = k.chieuNgang;
		giaBan = k.giaBan;
	}
	
	public Gach(String maSo, String color, int sl, int chieuDai, int chieuNgang, long giaBan) {
		this.maSo = new String(maSo); 
		this.color = new String (color); 
		this.sl = sl;
		this.chieuDai = chieuDai;
		this.chieuNgang = chieuNgang;
		this.giaBan = giaBan;
	}
	
	public void nhap(Scanner sc) {
		System.out.print("Nhap ma so: ");
		maSo = sc.nextLine();
		System.out.print("Nhap mau sac: ");
		color = sc.nextLine();
		System.out.print("Nhap so luong: ");
		sl = sc.nextInt();
		System.out.print("Nhap chieu dai: ");
		chieuDai = sc.nextInt();
		System.out.print("Nhap chieu ngang: ");
		chieuNgang = sc.nextInt();
		System.out.print("Nhap gia ban: ");
		giaBan = sc.nextInt();
	}
	
	
	public void hienThi() {
		System.out.println("Ma so: " + maSo + "\nMau sac: " + color);
		System.out.println("So luong " + sl + "\nChieu dai: " + chieuDai + "\nChieu ngang: " + chieuNgang + "\nGia Ban: " + giaBan);
	}
	
	public float giaBanLe() {
		float tmp = giaBan/sl;
		tmp += 0.2*tmp;
		return tmp;
	}

	public int dienTichToiDa() {
		return chieuDai*chieuNgang*sl;
	}
	
	public int soLuongHop(int D, int N) {
		int svd = D/chieuDai;
		if(D%chieuDai!=0) svd++;
		int svn = N/chieuNgang;
		if(N%chieuNgang!=0) svn++;
		int soVien= svd*svn;
		int soHop= soVien/sl;
		if(soVien%sl!=0) soHop++;
		return soHop;
	}
	
	public static void main(String[] args) {
		Gach k = new Gach();
		Scanner sc = new Scanner(System.in);
		k.nhap(sc);
		System.out.println(k.toString());
		System.out.printf("Gia ban le la: %.2f", k.giaBanLe());
	}
}
