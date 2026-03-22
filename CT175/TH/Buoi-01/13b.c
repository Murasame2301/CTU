#include <stdio.h>
#define MAX_N 100

typedef struct{
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
	pG->n = n;
	pG->m = 0;
	int i, j;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v) {
	pG->A[u][v]++;
	pG->m++;
}

int main() {
	Graph G; 
	int n, u, v; 
	scanf("%d", &n); 
	init_graph(&G, n);
	for (u = 1; u <= n; u++)
		for (v = 1; v <= n; v++){
			scanf("%d", &G.A[u][v]);
		}
	for(u = 1; u <= G.n; u++)
		for (v = 1; v <= G.n; v++) {
			int i = 0;
				while (i < G.A[u][v]) {
					printf("%d %d\n",u, v);
					i++;
				}
		}
	return 0; 
}
