//Da do thi co huong
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

int degree(Graph *pG, int u) {
	int deg_u = 0,v;
	for (v = 1; v <= pG->n; v++) {
		if(u == v && pG->A[u][v])
			deg_u += 2 * pG->A[u][v];
		else deg_u+=(pG->A[u][v] + pG->A[v][u]);
	}
	return deg_u;	
}

int outdegree(Graph *pG, int u) {
	int deg_u = 0,v;
	for (v = 1; v <= pG->n; v++) {
	    deg_u+=pG->A[u][v];
	}
	return deg_u;	
}

int main() { 
	Graph G; 
	int n, m, u, v; 
	scanf("%d%d", &n, &m); 
	init_graph(&G, n);
	int e;
	for (e = 0; e < m; e++) { 
		scanf("%d%d", &u, &v); 
		add_edge(&G, u, v); 
	} 
	for (u = 1; u <= n; u++) {
		printf("deg_out(%d) = %d\n", u, outdegree(&G, u));
	}
	return 0; 
} 
