package BaiTH4;

import java.util.Scanner;

import BaiTH3.SinhVien;

public class SinhVienCNTT extends SinhVien {
        private String taikhoan, matkhau, email;
        public SinhVienCNTT() {
        	
        }
        
        public SinhVienCNTT(SinhVienCNTT sv) {
        	super(sv);
        	this.taikhoan = sv.taikhoan;
        	this.matkhau = sv.matkhau;
        	this.email = sv.email;
        }
        
        public void nhap() {
            super.nhap();
            Scanner sc = new Scanner(System.in);
            System.out.println("Nhap tai khoan: ");
            taikhoan = sc.nextLine();
            System.out.println("Nhap mat khau: ");
            matkhau = sc.nextLine();
            System.out.println("Nhap email: ");
            email = sc.nextLine();
        }
        
        public String toString() {
            return super.toString() + "Tai Khoan: " + taikhoan + "\nMat Khau: " + matkhau + "\nEmail: " + email+"\n";
        }
        
        public void doiMatKhau(String newPass) {
        	this.matkhau = newPass;
        }
        
        String getEmail() {
        	return email;
        }
}
