#include <stdio.h>
#define MAX_M 20

typedef struct{
	int u, v;
} Edge;

typedef struct{
	int n,m;
	Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n) {
	pG->m = 0;
	pG->n = n;
}

void add_edge(Graph *pG, int u, int v) {
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->m++;
}

int degree(Graph *pG, int u) {
	int deg_u = 0, e;
	for(e = 0; e<pG->m; e++) {
		if(pG->edges[e].u == u)
			deg_u++;
		if(pG->edges[e].v == u)
			deg_u++;
	}
	return deg_u;
}

int main() {
	//freopen("dt.txt", "r", stdin);
	Graph G; 
	FILE *file = fopen("dt.txt", "r");
	int n, m;
	fscanf(file,"%d%d", &n, &m);
	init_graph(&G, n);
	int e,u, v;
	for(e = 0; e < m; e++) {
		fscanf(file,"%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	fclose(file);
	for (u = 1; u <= G.n; u++) 
		printf("deg(%d) = %d\n", u, degree(&G, u)); 
	return 0; 
} 
