#include <stdio.h>
#include <stdlib.h>
#define size 100
typedef struct{
	int PA;
	float TL, GT, DG;
	char TenDV[size];
} DoVat;

DoVat *ReadData(float *W, int *n){
	FILE *f = fopen("CaiBalo1.txt", "r");
	fscanf(f, "%f", W);
	DoVat *DS = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%f%f%[^\n]", &DS[i].TL, &DS[i].GT, &DS[i].TenDV);
		DS[i].DG = DS[i].GT/DS[i].TL;
		DS[i].PA = 0;
		i++;
		realloc(DS, sizeof(DoVat) * (i+1));
	}
	*n = i;
	fclose(f);
	return DS;
}

void swap(DoVat *a, DoVat *b){
	DoVat tmp = *a;
	*a = *b;
	*b = tmp;
}


void BubbleSort(DoVat DS[], int n){
	for(int i = 0; i < n-1; i++)
		for(int j = n-1; j >= 1; j--)
			if(DS[j-1].DG < DS[j].DG)
				swap(&DS[j-1], &DS[j]);
}

void TaoNutGoc(float W, float *V, float *TGT, float *CT, float *GLNTT, float DG_Max){
	*TGT = 0.0;
	*V = W;
	*GLNTT = 0.0;
	*CT = *V * DG_Max;
}

void UpdateGLNTT(float TGT, DoVat DS[], int n, float *GLNTT, int x[]){
	if(TGT > *GLNTT){
		*GLNTT = TGT;
		for(int i = 0; i < n; i++) DS[i].PA = x[i];
	}
}

void NhanhCan(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], DoVat DS[], int n){
	int SL = *V/DS[i].TL;
	for(int j = SL; j >= 0; j--){
		*TGT += j*DS[i].GT;
		*V -= j*DS[i].TL;
		*CT = *TGT + *V * DS[i+1].DG;
		if(i == n-1 || *V == 0){
			UpdateGLNTT(*TGT,DS,n,GLNTT,x);
		}
		else {
			NhanhCan(i+1, TGT, CT, V, GLNTT, x,DS, n);
		}
		x[i] = 0;
		*TGT -= j*DS[i].GT;
		*V += j*DS[i].TL;
	}
}

void PrintData(DoVat DS[], int n){
	printf("\nDanh sach cac do vat:\n");
	printf("\n|-STT-|----Ten Do Vat----|--TL--|--GT--|--DG--|--PA--|\n");
	for(int i = 0; i < n; i++){
		printf("|%-5d|%-18s|%-6.2f|%-6.2f|%-6.2f|%-6d|\n", i+1, DS[i].TenDV, DS[i].TL, DS[i].GT, DS[i].DG, DS[i].PA);
	}
}
int main(){
	int n, W;
	taoNutGoc(W, &V, &TGT, &CT, &GLNTT, dsdv[0].DG);
	nhanhCan(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	inDSDV(dsdv, n, W);
	free(dsdv);
	return 0;
}
