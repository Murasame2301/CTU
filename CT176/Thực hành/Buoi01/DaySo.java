package buoi1;

import java.util.Arrays;
import java.util.Scanner;

public class DaySo {
	private int []ds;
	private int n;
	
	public void nhap() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap n: ");
		n = sc.nextInt();
		ds = new int[n];
		for (int i = 0; i < n; i++) {
			System.out.println("Nhap so thu " + (i+1));
			ds[i] = sc.nextInt();
		}
		//sc.close();
	}
	
	public void hienthi() {
		for (int i = 0; i < n; i++) {
			System.out.print(ds[i] + " ");
		}
		System.out.println();
	}
	
	public int dem(int x) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (ds[i] == x) cnt++;
		}
		return cnt;
	}
	
	public void sort() {
		Arrays.sort(ds);
	}
	
	public void insertList(int x) {
		int [] ds1 = new int[n+1];
		for (int i = 0; i < n; i++) {
			ds1[i] = ds[i];
		}
		ds1[n] = x;
		Arrays.sort(ds1);
		ds = ds1;
		for (int i = 0; i < ds.length; i++) System.out.print(ds[i] + " ");
	}
	public void removeLessThanx(int x) {
		int f = 0;
		while (f < ds.length && ds[f] < x) {
			f++;
		}
		int [] ds2 = new int[n-f+1];
		int j = 0;
		for (int i = f; i < ds.length; i++) {
			ds2[j] = ds[i];
			j++;
		}
		ds = ds2;
		for (int i = 0; i < ds.length; i++) System.out.print(ds[i] + " ");
	}
	public static void main(String[] args) {
		DaySo d = new DaySo();
		d.nhap();
		Scanner sc = new Scanner(System.in);
		System.out.print("Nhap so x = ");
		int x = sc.nextInt();
		System.out.println("So " + x + " xuat hien " + d.dem(x) + " lan");
		d.sort();
		System.out.print("Danh sach sau khi sap xep la: ");
		d.hienthi();
		System.out.print("Danh sach sau khi chen x la: ");
		d.insertList(x);
		System.out.println();
		System.out.print("Danh sach sau khi xoa cac so nho hon x la: ");
		d.removeLessThanx(x);
	}
}
