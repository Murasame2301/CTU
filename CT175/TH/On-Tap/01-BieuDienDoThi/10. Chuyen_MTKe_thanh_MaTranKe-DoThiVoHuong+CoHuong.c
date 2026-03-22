#include <stdio.h>
#define MAX_N 100

int main(){
	int n, A[MAX_N][MAX_N];
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			A[i][j] = 0;
	for(int u = 1; u <= n; u++){
		int v;
		do{
			scanf("%d", &v);
			if(v != 0) A[u][v]++;
		}while(v != 0);
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
	return 0;
}
