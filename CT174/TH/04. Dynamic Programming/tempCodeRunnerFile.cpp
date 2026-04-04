#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char TenDV[20];
	int TL, GT, PA;
}DoVat;	

typedef int bang[50][50];

DoVat *ReadFromFile(int *W, int *n){
	File *f = fopen("QHD_CaiBalo.INP", "r");
	fscanf(f, "%d", W);
	DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f)){
		fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
		dsdv[i].GT = 0;
		i++;
		dsdv=(DoVat*)realloc(sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}


DoVat *ReadFromFile(int *W, int *n){
	File *f = fopen("QHD_CaiBalo.INP", "r");
	fscanf(f, "%d", W);
	DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
		dsdv[i].PA = 0;
		i++;
		dsdv=(DoVat*)realloc(sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

DoVat *ReadFromFile(int *W, int *n){
	File *f = fopen()
}
