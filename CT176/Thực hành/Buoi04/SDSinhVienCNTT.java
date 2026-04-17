package BaiTH4;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;


public class SDSinhVienCNTT {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("Nhap so luong sinh vien CNTT: ");
		int n = sc.nextInt();
		sc.nextLine();
		System.out.println("\nNhap ds Sinh Vien CNTT: ");
		SinhVienCNTT[] ds = new SinhVienCNTT[n];
		for (int i = 0; i < n; i++) {
			System.out.println("Nhap sv thu " + (i + 1));
			ds[i] = new SinhVienCNTT();
			ds[i].nhap();
			ds[i].nhapDiem();
		}
		System.out.println("Ds sau khi nhap xong:");
		for (SinhVienCNTT x: ds) System.out.println(x);
		
		try {
			ObjectOutputStream os = new ObjectOutputStream(
					new FileOutputStream("sv.ser"));
			os.writeObject(ds);
			os.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		SinhVienCNTT []ds1 = new SinhVienCNTT[n];
		//doc file
			
		try {
				ObjectInputStream is = new ObjectInputStream(
						new FileInputStream("sv.ser"));
				ds1 = (SinhVienCNTT[]) is.readObject();
				is.close();
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			System.out.println("Danh sach ds1 la:");
			for (int i = 0; i < n; i++)
				System.out.println(ds1[i]);
			
			System.out.println("\nNhap email can tim:");
			String mail = new String(sc.nextLine());
			for (int i = 0; i < n; i++)
				if (ds1[i].getEmail().equals(mail)) {
					 ds1[i].hienThiDiem();
					 System.out.println();
					 break;
				}
			
			Arrays.sort(ds1, new Comparator<SinhVienCNTT>() {
			    @Override
			    public int compare(SinhVienCNTT a, SinhVienCNTT b) {
			        return Float.compare(b.diemTB(), a.diemTB());
			    }
			});
			
			for (int i = 0; i < n; i++) 
					System.out.println(ds1[i]);
	}
}