#include <stdio.h>
#define MAX_N 100
#define oo 10000000

int mark[MAX_N][MAX_N], pi[MAX_N][MAX_N], A[MAX_N][MAX_N];
int di[] = {-1, 1, 0 ,0};
int dj[] = {0 ,0, -1, 1};

void Dijkstra(int A[][MAX_N], int n, int m){
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			pi[i][j] = oo;
	pi[1][1] = 0;
	for(int it = 0; it < n*m; it++){
		int u, v, min_pi = oo;
        for(int i = 1; i <= m; i++){
        	for (int j = 1; j <= n ; j++)
	            if (!mark[i][j] && pi[i][j] < min_pi) {
	                min_pi = pi[i][j];
	                u = i; v = j;
	            }
        }
		mark[u][v] = 1;
		
		for(int i = 0; i < 4; i++){
			int new_u = u + di[i];
			int new_v = v + dj[i];
            if (new_u >= 1 && new_u <= m && new_v >= 1 && new_v <= n && !mark[new_u][new_v]){
                if (pi[new_u][new_v] > pi[u][v] + A[new_u][new_v]){
                    pi[new_u][new_v] = pi[u][v] + A[new_u][new_v];
                }
            }
		}
	}
}
int main(){
	int n,m;
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &A[i][j]);
	Dijkstra(A, n, m);
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++)
			printf("%d ", pi[i][j]);
		printf("\n");
	}
	printf("%d", pi[m][n]);

	return 0;
}
