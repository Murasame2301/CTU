#include <stdio.h>
#include <stdlib.h>
#define size 50

typedef struct{
	float DoDai;
	int dau,cuoi;
} Canh;

Canh *ReadData(int *n){
	FILE *f = fopen("TSP.txt", "r");
	Canh *tmp = (Canh*)malloc(sizeof(Canh));
	fscanf(f, "%d", n);
	int k = 0;
	for(int i = 0; i < *n; i++)
		for(int j = 0; j < *n; j++){
			float x;
			fscanf("%f", &x);
			if(j > i){
				tmp.dau = i;
				tmp.cuoi = j;
				tmp.DoDai = x;
				k++;
			}
		}
	tmp = (Canh*)realloc(tmp,sizeof(Canh) * (k));
	fclose(f);
	return tmp;
}

void swap(Canh *a, Canh *b){
    Canh tmp=*a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(Canh a[], int n){
    int i,j;
    n=n*(n-1)/2;
    for(i = 1;i <= n-1;i++)
        for(j=n-1;j >= i;j--){
            if(a[j-1].DoDai > a[j].DoDai){
                swap(&a[j-1],&a[j]);
            }
        }
}

int DinhCap3(Canh PA[], int m, Canh moi){
    int i = 0, dem = 1;
    while(i<k && dem!=3){
        if(PA[i].dau==moi.dau || PA[i].cuoi==moi.dau) dem++;
        i++;
    }
    if(dem==3) return 1;

    i=0; dem=1;
    while(i<k && dem!=3){
        if(PA[i].dau==moi.cuoi || PA[i].cuoi==moi.cuoi) dem++;
        i++;
    }
    return dem==3;
}

void init_forest(int parent[], int n){
	int i;
	for(i = 0; i < n; i++)
		parent[i] = i;
}

int find_root(int parent[],int u){
    while(u != parent[u]){
        u = parent[u];
    }
    return u;
}

int ChuTrinh(int dau, int cuoi){
	return dau == cuoi;
}

void update_forest(int parent[], int u, int v){
	parent[v] = u;
}

void InDSCanh(Canh DSCanh[], int m){
	
}

int main() {
	int n;
	Canh *DSCanh = ReadData(&n);
	printf("\nDanh sach canh ban dau:\n")
	InDSCanh(&DSCanh, n*(n-1)/2);
	return 0;
}
