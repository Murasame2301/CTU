package buoi1;

import java.util.Scanner;

public class PtBac2 {
	public static void giaiPtBac2(float a, float b, float c) {
		if (a == 0)
			System.out.println("Khong phai la pt bac 2!!!");
		else {
				float delta = b*b - 4 * a * c;
				if (delta == 0) 
						System.out.printf("Pt bac 2 co nghiem kep la: x1 = x2 = %.2f", -b/(2*a));
				else if (delta > 0) {
					System.out.println("Pt co 2 nghiem phan biet:\n");;
					System.out.printf("x1 = %.2f\n", (-b + Math.sqrt(delta))/(2 * a));
					System.out.printf("x2 = %.2f", (-b - Math.sqrt(delta))/(2 * a));
			}
				else System.out.println("Phuong trinh vo nghiem!!!");
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Nhap ba so a, b, c:");
		float A = sc.nextFloat(), B = sc.nextFloat(), C = sc.nextFloat();
		sc.close();
		giaiPtBac2(A, B, C);
	}
}
