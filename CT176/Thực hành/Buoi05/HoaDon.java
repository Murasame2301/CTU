package BaiTH5;

import java.util.Scanner;

public class HoaDon {
	private String mso, tde,nvien;
	private KhachHang kh;
	private Date nglap;
	private ChiTiet c[];
	
	
	public HoaDon() {
		this.mso = new String();
		this.tde = new String();
		this.nvien = new String();
		this.kh = new KhachHang();
		this.nglap = new Date();
		this.c = new ChiTiet[20];
	}
	
	public HoaDon(HoaDon h) {
		this.mso = h.mso;
		this.tde = h.tde;
		this.nvien = h.nvien;
		this.kh = h.kh;
		c = new ChiTiet[20]; int i = 0;
		for (ChiTiet t: h.c) {
			if (t == null) break;
			c[i] = t;
			i++;
		}
	}
	
	

	public Date getNglap() {
		return nglap;
	}

	public void setNglap(Date nglap) {
		this.nglap = nglap;
	}

	public void nhap() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap ma so hoa don: ");
		mso = sc.nextLine();
		System.out.println("Nhap tieu de hoa don: ");
		tde = sc.nextLine();
		System.out.println("Nhap nhan vien quan ly: ");
		nvien = sc.nextLine();
		System.out.println("Nhap thong tin khach hang: ");
		System.out.println("Ban co phai la khach hang VIP khong? (y/n)");
		char ch = sc.nextLine().charAt(0);
		if (ch == 'y')
			kh = new KhachHangVIP();
		else
			kh = new KhachHang();
		kh.nhap();
		System.out.println("Nhap ngay lap hoa don: ");
		nglap.nhap(sc);
		System.out.println("Hoa don co bao nhieu chi tiet?");
		int n = sc.nextInt();
		sc.nextLine();
		for (int i=0; i<n; i++) {
			c[i]= new ChiTiet();
			System.out.println("\nNhap Chi Tiet thu " + (i+1));
			c[i].nhap();
		}
	}
	
	public void in() {
		System.out.println("\n\n========\t========\t=========\t==========\t===========\t\n");
		System.out.println("\t\t" + tde.toUpperCase());
		System.out.println("\tMa so:" + mso);
		System.out.println("Thong tin khach hang: " + kh);
		System.out.println ("Ngay lap: " + nglap);
		System.out.println("Nguoi lap hoa don: " + nvien);
		System.out.println("\nChi Tiet hoa don :");
		System.out.println("-------------------------------------------------------");
		for (ChiTiet t: c) {
			if (t==null) break;
			t.in();
		}
		System.out.println("-------------------------------------------------------");
		System.out.printf("Tong don hang la : %.2f", tong());
	}
	
	
	public float tong() {
		float S = 0.0f;
		for (ChiTiet t: c) {
			if (t == null) break;
			S += t.tong();
		}
		return S - S * (kh.getTLeGiam()/100);
	}
}
