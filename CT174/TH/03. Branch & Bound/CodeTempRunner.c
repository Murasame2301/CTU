#include <stdio.h>
typedef struct{
	int dau, cuoi, da_dung;
	float do_dai;
} canh;

void reset(canh a[][size], int n){
	int i, j;
	for(i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j].da_dung = 0;
}
float Canh_NN(canh a[][size], int n){
	float Cmin = 3.30482e+38;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i != j && !a[i][j].da_dung && a[i][j].do_dai < Cmin)
				Cmin = a[i][j].do_dai;
	return Cmin;
}

float can_duoi(canh a[][size], float *TGT, int n, int i){
	return TGT + Canh_NN(a,n) * (n-i);
}

int co_chu_trinh(canh x[], int k, int ke_tiep){
	int i = 0, coCT = 0;
	while (i < k && !coCT){
		if(x[i].dau == ke_tiep) coCT = 1;
		else i++;
	}
}

void UpdatePA_TNTT(canh a[][size], int n, float TGT, float *GNNTT, canh [], canh PA[]){
	x[n-1] = a[x[n-2].cuoi][x[0].dau];
	TGT += x[n-1].do_dai;
	if(*GNNTT > TGT){
		for(int i = 0; i < n; i++) PA[i] = x[i];
	}
}

void NhanhCan(canh a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, canh x[], canh PA[]){
	for(int j = 0; j < n; j++)
		if (dau != j && !a[dau][j].da_dung && !has_cycle(x, i, j)){
			
			*TGT = *TGT + a[dau][j].do_dai;
			*CD = can_duoi(a, *TGT, n, i+1);
			if(*CD < *GNNTT){
				x[i] = a[dau][j];
				a[dau][j].da_dung=1;
				a[j][dau].da_dung = 1;
				if(i == n-2){
					Cap_Nhat_PA_TNTT(a, n, *TGT, GNNTT, x, PA);
				}
				else{
					Nhanh_Can(a, n, i+1, j, TGT, CD, GNNTT, x, PA);
				}
			}
			*TGT = *TGT - a[dau][j].do_dai;
			a[dau][j].da_dung = 0;
			a[j][dau].da_dung = 0;
		}
}
int main(){
	return 0;
}
