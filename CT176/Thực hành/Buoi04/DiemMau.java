package BaiTH4;

import java.util.Scanner;
import BaiTH2.Diem;

public class DiemMau extends Diem {
	private String mau;
	
	public DiemMau() {
		mau = "den";
	}

	public DiemMau(DiemMau k) {
		super(k);
		mau = k.mau;
	}

	public DiemMau(int x, int y, String mau) {
		super(x, y);
		this.mau = mau;
	}
	
	public void GanMau(String mau) {
		this.mau = mau;
	}
	
    public String getMau() {
		return mau;
	}

	public void setMau(String mau) {
		this.mau = mau;
	}

	public void nhap() {
		System.out.println("Nhap toa do: ");
        super.nhap();
        Scanner sc = new Scanner(System.in);
        System.out.println("Nhap mau: ");
        mau = sc.nextLine();
    }
    
    public void hienThi(){
        super.hienThi();
        System.out.println();
        System.out.println("Mau: " + mau);
    }

}
