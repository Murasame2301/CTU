#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char TenDV[20];
	float DG;
	int TL, GT, PA;
} DoVat;

DoVat *ReadData(int *W, int *n){
	FILE *f = fopen("bag1.txt", "r");
	fscanf(f,"%d",W);
	int i = 0;
	DoVat *DV = (DoVat*)malloc(sizeof(DoVat));
	while (!feof(f)){
		fscanf(f,"%d%d%[^\n]",&DV[i].TL, &DV[i].GT, &DV[i].TenDV);
		DV[i].DG = (float)DV[i].GT / DV[i].TL;
		DV[i].PA = 0;
		i++;
		DV = realloc(DV,sizeof(DoVat)*(i+1));
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

void bubbleSort(DoVat t[], int n){
	int i,j;
	for(int i = 0; i < n-1; i++)
		for(j = n-1; j >= i+1; j--)
			if(t[j-1].DG < t[j].DG)
				swap(&t[j-1],&t[j]);
}

void greedy(DoVat DV[], int n, int W, int *W_remainder){
	bubbleSort(DV, n);
	int i = 0;
	while (W > 0 && i < n){
		DV[i].PA = W/DV[i].TL;
		W = W - (DV[i].PA * DV[i].TL);
		i++;
	}
	*W_remainder = W;
}

void InDS(DoVat DV[], int n, int W, int W_remainder){
	printf("\nBai toan cai balo 1 giai bang thuat toan THAM LAM:\n");
	printf("\n|-STT-|----Ten Do Vat----|--TL--|--GT--|--DG--|--PA--|\n");
	for(int i = 0; i < n; i++){
		printf("|%-5d|%-18s|%-6d|%-6d|%-6.2f|%-6d|\n", i+1,DV[i].TenDV,DV[i].TL,DV[i].GT, DV[i].DG,DV[i].PA);
	}
	int TGT = 0;
	printf("Phuong an (tu cao den thap): (");
	for(int i = 0; i < n; i++){
		if (i == n - 1) printf("%d",DV[i].PA);
		else printf("%d, ",DV[i].PA);
		TGT+=(DV[i].PA * DV[i].GT);
	}
	printf(")\n");
	printf("Tong Trong Luong: %d\n", W - W_remainder);
	printf("Tong Gia Tri: %d\n", TGT);
	
}

int main() {
	int W,n, W_remainder;
	DoVat *DV = ReadData(&W, &n);
	greedy(DV, n, W, &W_remainder);
	InDS(DV,n,W,W_remainder);
	return 0;
}
