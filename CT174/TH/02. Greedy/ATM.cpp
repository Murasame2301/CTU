#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int sotien, PA;
	char loaitien[50];
} Tien;

Tien* ReadData(int *n){
	FILE *f = fopen("atm.txt", "r");
	Tien* DSLoaiTien = (Tien*)malloc(sizeof(Tien));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%d%[^\n]",&DSLoaiTien[i].sotien, &DSLoaiTien[i].loaitien);
		DSLoaiTien[i].PA = 0;
		i++;
		realloc(DSLoaiTien, sizeof(Tien) *(i+1));
	}
	*n = i;
	fclose(f);
	return DSLoaiTien;
}

void PrintData(Tien DS[], int n, int TienRut, int TienThua){
	printf("Danh sach cac menh gia tien:\n");
	printf("\n|-STT-|-------Loai Tien-------|---MG---|--PA--|\n");
	for(int i = 0; i < n; i++)
		printf("|%-5d|%-23s|%-8d|%-6d|\n", i+1, DS[i].loaitien, DS[i].sotien, DS[i].PA);
	printf("So tien da rut: ", TienRut - TienThua);
}

void swap(Tien *a, Tien *b){
	Tien tmp = *a;
	*a = *b;
	*b = tmp;
}
void BubbleSort(Tien DS[], int n){
	for(int i = 0; i < n-1; i++)
		for(int j = n-1; j >= 1; j--)
			if(DS[j-1].sotien < DS[j].sotien)
				swap(&DS[j-1], &DS[j]);
}
void greedy(Tien DS[], int n, int *TienRut, int *TienThua){
	for(int i = 0; i < n; i++){
		DS[i].PA = *TienRut/DS[i].sotien;
		*TienRut -= DS[i].PA * DS[i].sotien;
	}
	*TienThua = *TienRut;
}
int main(){
	int n, TienRut = 250000, TienThua = 0;
	Tien *DS = ReadData(&n);
	BubbleSort(DS, n);
	printf("Bai toan ATM\n");
	printf("Nhap so tien can rut: ");
	greedy(DS, n, &TienRut, &TienThua);
	//scanf("%d", &tmp);
	PrintData(DS, n, TienRut, TienThua);
	
	return 0;
}
