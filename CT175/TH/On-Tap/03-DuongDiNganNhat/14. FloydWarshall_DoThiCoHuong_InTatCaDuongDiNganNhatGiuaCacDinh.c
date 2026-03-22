#include <stdio.h>
#define MAX_N 500
#define oo 10000000
typedef struct{
	int W[MAX_N][MAX_N];
	int n,m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			pG->W[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->W[u][v] = w;
}

int pi[MAX_N][MAX_N], next[MAX_N][MAX_N], idx;

void FloydWarshall(Graph *pG){
	int u, v, k;
	for(u = 1; u <= pG->n; u++)
		for(v = 1; v <= pG->n; v++){
			pi[u][v] = oo;
			next[u][v] = -1;
		}
		
	for(u = 1; u <= pG->n; u++)
		pi[u][u] = 0;
		
	for(u = 1; u <= pG->n; u++)
		for(v = 1; v <= pG->n; v++)
			if(pG->W[u][v] != 0){
				pi[u][v] = pG->W[u][v];
				next[u][v] = v;
			}
	for(k = 1; k <= pG->n; k++)
		for(u = 1; u <= pG->n; u++)
			for(v = 1; v <= pG->n; v++)
				if(pi[u][k] != oo && pi[k][v] != oo && pi[u][k] + pi[k][v] < pi[u][v]){
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
}


int main(){
	int n,m;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	FloydWarshall(&G);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++){
			printf("path(%d, %d):", i, j);
			int u = i;
			if(pi[u][j] == oo) printf(" NO PATH\n");
			else {
				while (u != j){
					printf(" %d ->", u);
					u = next[u][j];
				}
				printf(" %d\n", j);
			}
		}
	return 0;
}
