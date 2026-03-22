#include <stdio.h>
#define MAX_N 500

typedef struct{
	int A[MAX_N][MAX_N];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->m++;
}

int degree(Graph *pG, int u){
	int deg_u = 0;
	for(int v = 1; v <= pG->n; v++){
		deg_u += (pG->A[u][v] + pG->A[v][u]);
	}
	return deg_u;
}

int indegree(Graph *pG, int u){
	int indeg_u = 0;
	for(int v = 1; v <= pG->n; v++){
		indeg_u += pG->A[v][u];
	}
	return indeg_u;
}

int outdegree(Graph *pG, int u){
	int outdeg_u = 0;
	for(int v = 1; v <= pG->n; v++){
		outdeg_u += pG->A[u][v];
	}
	return outdeg_u;
}

void neighbours(Graph *pG, int u){
	printf("neighbours(%d) = ", u);
	for(int v = 1; v <= pG->n; v++)
		if(pG->A[u][v])
			printf("%d ", v);
	printf("\n");
}

int main(){
	freopen("dt.txt","r", stdin);
	int n, m;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
    for (int u = 1; u <= G.n; u++) {
        for (int v = 1; v <= G.n; v++)
            printf("%d ", G.A[u][v]);
        printf("\n");	
    }
	for(int i = 1; i <= G.n; i++){
		printf("degree[%d] = %d\n", i, degree(&G, i));
	}
	return 0;
}
