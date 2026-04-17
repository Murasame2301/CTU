package BaiTH2;

import java.util.Scanner;

public class PhanSo {
	private int tu, mau;
	public PhanSo() {
		
	}
	
	public PhanSo(int a, int b) {
		if (a > 0 && b < 0) {
			tu = -a;
			mau = Math.abs(b);
		}
		else if (a < 0 && b < 0) {
			tu = Math.abs(a);
			mau = Math.abs(b);
		}
		else {
			tu = a;
			mau = b;
		}
	}
	
	public void nhapPhanSo(Scanner sc) {
		do {
			tu = sc.nextInt();
			mau = sc.nextInt();
			System.out.print("Phan so vua nhap khong hop le!!!\nNhap lai: ");
		} while (mau == 0);
		int k = Math.abs(gcd(tu, mau));
		tu /= k;
		mau /= k;
	}
	
	public void hienThi() {
		if (tu == 0) System.out.print("0 ");
		else if (mau == 1) System.out.print(tu + " ");
		else {
			System.out.print(tu + "/" + mau + " ");
		}
	}
	
	public void nghichDao() {
		if (tu != 0) {
			int t = tu;
			tu = mau;
			mau = t;
		}
		else System.out.println("Phan so khong co gia tri nghich dao");
	}
	
	public PhanSo giaTriNghichDao() {
		PhanSo k = new PhanSo();
		if (tu != 0) {
				k.tu = mau;
				k.mau = tu;
		}
		return k;
	}
	
	public int gcd(int a, int b) {
		if (b == 0) return a;
		else return gcd(b, a % b);
	}

	
	public float giaTriThuc() {
		return (float) tu/mau;
	}
	
	public boolean lonHon(PhanSo a) {
		if (giaTriThuc() > a.giaTriThuc()) return true;
		else return false;
	}
	
	public PhanSo rutGon() {
		PhanSo res = new PhanSo();
		int k = Math.abs(gcd(tu, mau));
		res.tu = tu/k;
		res.mau = mau/k;
		return res;
	}
	
	public PhanSo congPhanSo(PhanSo a) {
		PhanSo res = new PhanSo();
		int msc = mau / gcd(mau, a.mau) * a.mau;
		res.mau = msc;
		res.tu = (msc / a.mau) * a.tu + (msc / mau) * tu;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo truPhanSo(PhanSo a) {
		PhanSo res = new PhanSo();
		int msc = mau / gcd(mau, a.mau) * a.mau;
		res.mau = msc;
		res.tu = (msc / a.mau) * a.tu - (msc / mau) * tu;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo nhanPhanSo(PhanSo a) {
		PhanSo res = new PhanSo();
		res.mau = a.mau * mau;
		res.tu = a.tu * tu;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo chiaPhanSo(PhanSo a) {
		PhanSo res = new PhanSo();
		res.tu = tu * a.mau;
		res.mau = mau * a.tu;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo congSoNguyen(int a) {
		PhanSo res = new PhanSo();
		res.mau = mau;
		res.tu = mau * a + tu;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo truSoNguyen(int a) {
		PhanSo res = new PhanSo();
		res.mau = mau;
		res.tu = tu - a * mau;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo nhanSoNguyen(int a) {
		PhanSo res = new PhanSo();
		res.mau = mau;
		res.tu = tu * a;
		res = res.rutGon();
		return res;
	}
	
	public PhanSo chiaSoNguyen(int a) {
		PhanSo res = new PhanSo();
		res.mau = mau * a;
		res.tu = tu;
		res = res.rutGon();
		return res;
	}
	

}
