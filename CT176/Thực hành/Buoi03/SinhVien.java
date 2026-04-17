package BaiTH3;

import java.util.Scanner;

import BaiTH2.Date;

public class SinhVien implements Comparable{
	 private String mssv, hoTen;
	 private Date ngaySinh;
	 private int slhp;
	 private String[] tenhp, diemhp;
	private final int max =100;
	 public SinhVien() {
		 ngaySinh = new Date();
		 tenhp = new String[max];
		 diemhp = new String[max];
	 }
	 
	 public SinhVien(SinhVien a) {
		 this.mssv = a.mssv;
		 this.ngaySinh = a.ngaySinh;
		 this.slhp = a.slhp;
		 this.tenhp = a.tenhp;
		 this.tenhp = new String[max];
		 this.diemhp =new String[max];
		 for(int i=0; i<slhp ;i++) {
			tenhp[i]= new String(a.tenhp[i]);
			tenhp[i]= new String(a.diemhp[i]);
		}
	 }
	 public void nhap(Scanner sc) {
		 System.out.print("Nhap mssv: ");
		 mssv = sc.nextLine();
		 System.out.print("Nhap ho ten: ");
		 hoTen = sc.nextLine();
		 System.out.println("Nhap ngay sinh: ");
		 ngaySinh.nhap(sc);
	 }
	 
	 public void nhapDiem(Scanner sc) {
		 System.out.print("Nhap so luong hoc phan: ");
		 slhp = sc.nextInt();
		 sc.nextLine();
		 for (int i = 0; i < slhp; i++) {
			 System.out.print("Nhap ten hp thu " + (i+1) + ": ");
			 tenhp[i] = sc.nextLine();
			 System.out.print("Nhap diem: ");
			 diemhp[i] = sc.nextLine();
		 }
	 }
	 
	 public void hienthi() {
		 System.out.println("MSSV: " + mssv);
		 System.out.println("Ho Ten: " + hoTen);
		 System.out.print("Ngay sinh: ");
		 ngaySinh.hienThi();
		 System.out.println();
		 System.out.println("Diem hp:");
		 for (int i = 0; i < slhp; i++) {
			 System.out.println((i + 1) + ". " + tenhp[i] + ": " + diemhp[i]);
		 }
	 }
	public String toString() {
			String s="";
			s+="Thong tin cua sinh vien " + hoTen + ":\n";
			s+="- MSSV: " + mssv + "\n";
			s+="- Ngay sinh: "+ ngaySinh.getNgay() + "/"+ ngaySinh.getThang() + "/" + ngaySinh.getNam()+ "\n";
			s+="- So luong hoc phan da dang ky: " + slhp + "\n";
			for (int i = 0; i < slhp; i++)
				s+= (i+1) + ". " + tenhp[i] + ": " + diemhp[i] + "\n";
			return s;
		}
	
	public String getMSSV() {
		return mssv;
	}
	
	public String getHoTen() {
		return hoTen;
	}
	public void dangKihp(String hp) {
		tenhp[slhp] = new String(hp);
		diemhp[slhp] = new String();
		slhp++;
	}

	public void xoahp(String hp) {
		for (int i = 0; i < slhp; i++) {
			if (tenhp[i].equals(hp)) {
				for (int j = i; j < slhp - 1; j++) {
					tenhp[j] = tenhp[j+1];
					diemhp[j] = diemhp[j + 1];
				}
				slhp--;
			}
		}
	}
	
	public float diemTB() {
		float d = 0.0f;
		for (int i = 0; i < slhp; i++) {
			if (diemhp[i].equals("A")) d+=4;
			else if (diemhp[i].equals("B+")) d+=3.5;
			else if (diemhp[i].equals("B")) d+=3;
			else if (diemhp[i].equals("C+")) d+=2.5;
			else if (diemhp[i].equals("C")) d+=2;
			else if (diemhp[i].equals("D+")) d+=1.5;
			else if (diemhp[i].equals("D")) d+=1;
		}
		return d/slhp;
	}

	@Override
	public int compareTo(Object o) {
		return hoTen.compareTo(((SinhVien)o).hoTen);
	}
}
