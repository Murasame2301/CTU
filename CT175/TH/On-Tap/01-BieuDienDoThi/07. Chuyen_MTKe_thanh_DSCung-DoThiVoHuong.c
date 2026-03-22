#include <stdio.h>
#define MAX_N 100

int main(){
	int A[MAX_N][MAX_N], n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d",&A[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			if(A[i][j] != 0){
				int t = 0;
				while (t < A[i][j]){
					printf("%d %d\n", i, j);
					t++;
				}
			}
	return 0;
}
