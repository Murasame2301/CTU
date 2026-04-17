package buoi1;

import java.util.Scanner;

public class nhapN {
	public static boolean isPrimeNumber(int x) {
		if (x < 2) return false;
		for (int i = 2; i < Math.sqrt(x); i++) {
			if (x % i == 0) return false;
		}
		return true;
	}
	
	public static void hienThiNhiPhan(int x) {
		int m, q = x;
		StringBuilder sb = new StringBuilder();
		while (q != 0) {
			m = q % 2;
			sb.append(m);
			q /= 2;
		}
		System.out.println("Dang nhi phan cua " + x + " la: " + sb.reverse());
	}
	public static int tongCacChuSo(int x) {
		int q = x, s = 0;
		while (q != 0) {
			int t = q % 10;
			s += t;
			q /= 10;
		}
		return s;
	}
	
	public static void uocNT(int x) {
        if (x <= 1) {
            System.out.println("Khong co uoc NT cua " + x);
            return;
        }
        System.out.print("Uoc NT cua " + x + " la: ");
        
        for (int i = 2; i < Math.sqrt(x); i++) {
        	int cnt = 0;
        	while (x % i == 0) {
        		if (cnt == 0) {
        			System.out.print(i + " "); cnt++;
        		}
        		x /= i;
        	}
        }
        if (x > 1) System.out.println(x);
	}
	
	public static void nhapN() {
		System.out.print("Nhap so N = ");
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		System.out.println("\nKTNguyenTo: " + isPrimeNumber(n));
		hienThiNhiPhan(n);	
		System.out.println("Tong cac chu so cua " + n + " la: " +tongCacChuSo(n));
		uocNT(n);
		sc.close();
	}
	public static void main(String[] args) {
		nhapN();
	}
}
