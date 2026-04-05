#include <stdio.h>
#include <stdlib.h>
#define min(x,y) (x>y)?y:x

typedef struct{
	int TL,GT,PA,SL;
	float DG;
	char TenDV[20];
}DoVat;

DoVat* ReadData(int *W, int *n){
	FILE *f = fopen("bag3.txt", "r");
	fscanf(f,"%d", W);
	DoVat *DV = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%d%d%[^\n]", &DV[i].TL, &DV[i].GT, &DV[i].TenDV);
		DV[i].PA = 0;
		DV[i].SL = 1;
		DV[i].DG =(float)DV[i].GT / DV[i].TL;
		i++;
		DV = realloc(DV, sizeof(DoVat) * (i+1));
	}
	*n = i;
	fclose(f);
	return DV;
}
void swap(DoVat *a, DoVat *b){
	DoVat tmp = *a;
	*a = *b;
	*b = tmp;
}
void bubbleSort(DoVat DV[], int n){
	for(int i = 0; i < n-1; i++)
		for(int j = n-1; j >= 1; j--)
			if(DV[j-1].DG < DV[j].DG)
				swap(&DV[j-1], &DV[j]);
}

void greedy(DoVat DV[], int n, int W, int *W_remainder){
	bubbleSort(DV, n);
	int i =0;
	while(i < n && W > 0){
		DV[i].PA = min(DV[i].SL, W/DV[i].TL);
		W -= (DV[i].PA * DV[i].TL);
		i++;
	}
	*W_remainder = W;
}

void InDS(DoVat DV[], int n, int W, int W_remainder){
	printf("\nBai toan Balo 3 giai bang tham an la:\n");
	printf("\n|-STT-|----Ten Do Vat----|--TL--|--GT--|--SL--|--DG--|--PA--|\n");
	for(int i = 0; i < n; i++){
		printf("|%-5d|%-18s|%-6d|%-6d|%-6d|%-6.2f|%-6d|\n", i+1, DV[i].TenDV, DV[i].TL, DV[i].GT, DV[i].SL, DV[i].DG, DV[i].PA);
	}
	printf("Phuong An (Tu cao xuong thap): (");
	int TGT = 0;
	for(int i = 0; i < n; i++){
		TGT += DV[i].PA * DV[i].GT;
		if(i == n-1) printf("%d)\n", DV[i].PA);
		else printf("%d, ", DV[i].PA);
	}
	printf("Tong trong luong: %d\n", W - W_remainder);
	printf("Tong gia tri: %d", TGT);
}

int main(){
	int W,n,W_remainder;
	DoVat *DV = ReadData(&W, &n);
	greedy(DV,n,W,&W_remainder);
	InDS(DV, n, W, W_remainder);
	return 0;
}
