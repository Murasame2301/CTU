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
			pG->W[i][j] = oo;//Do Moore Dijkstra ap dung do thi trong so "khong am"
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->W[u][v] = w;
	pG->W[v][u] = w;
}

int p[MAX_N], mark[MAX_N], pi[MAX_N];

void Dijkstra(Graph *pG, int s){
	for(int u = 1; u <= pG->n; u++){
		pi[u] = oo;
		p[u] = -1;
		mark[u] = 0;
	}
	pi[s] = 0;
	for(int i = 1; i <= pG->n - 1; i++){
		int min_pi = oo;
		int u = -1;
        for(int j = 1; j <= pG->n; j++)
            if (!mark[j] && pi[j] < min_pi) {
                min_pi = pi[j];
                u = j;
            }
		if(u == -1) break;
	
		mark[u] = 1;
	
		for(int v = 1; v <= pG->n; v++)
			if(pG->W[u][v] != oo && !mark[v]){
				if(pi[u] + pG->W[u][v] < pi[v]){
				    pi[v] = pi[u] + pG->W[u][v];
				    p[v] = u;
				}
			}
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
	Dijkstra(&G, 1);
	for(int i = 1; i <= n; i++)
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
	return 0;
}
