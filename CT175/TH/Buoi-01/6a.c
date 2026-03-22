//Do thi vo huong
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

int adjacent(Graph *pG, int u, int v) {
	int e;
	for (e = 0; e < pG->m; e++){
		if ((pG->edges[e].u == u && pG->edges[e].v == v) || (pG->edges[e].u == v && pG->edges[e].v == u))
			return 1;
	}
	return 0;
}

void neighbours(Graph *pG, int u){
	printf("neighbours(%d) = ", u);
	int v;
	for (v = 1; v <= pG->n; v++) {
		if (adjacent(pG, u, v)) printf("%d ", v);
	}
	printf("\n");
}

int main() {
	Graph G; 
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	int e,u, v;
	for(e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(u = 1; u <= G.n; u++) {
		neighbours(&G, u);
	}
	return 0; 
} 
