#include <stdio.h>
#define MAX_N 100
#define MAX_M 500

typedef struct{
	int u, v;
}Edge;

typedef struct{
	Edge edges[MAX_M];
	int n, m;
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}
/*
1>
Kiem tra hop le cung (u,v)
void add_edge(Graph *pG, int u, int v){
	if(u >= 1 && v >= 1 && u <= pG->n && v <= pG->n){
		pG->edges[pG->m].u = u;
		pG->edges[pG->m].v = v;
		pG->m++;
	}
}
*/
//2>
	//Kiem tra hop le cung (u,v)
	//Kiem tra cung (u, v) hoac (v, u) da ton tai -> khong them
void add_edge(Graph *pG, int u, int v){
	for(int e = 0; e < pG->m; e++){
		if((pG->edges[e].u == u && pG->edges[e].v == v)
			|| (pG->edges[e].u == v && pG->edges[e].v == u))
		return;
	}
	if(u >= 1 && v >= 1 && u <= pG->n && v <= pG->n){
		pG->edges[pG->m].u = u;
		pG->edges[pG->m].v = v;
		pG->m++;
	}
}

int adjacent(Graph *pG, int u, int v){
	for(int e = 0; e < pG->m; e++){
		if((pG->edges[e].u == u && pG->edges[e].v == v) 
			|| (pG->edges[e].u == v && pG->edges[e].v == u))
				return 1;
	}
	return 0;
}

int degree(Graph *pG, int u){
	int deg_u = 0;
	for(int e = 0; e <= pG->m; e++){
		if(pG->edges[e].u == u)
			deg_u++;
		if(pG->edges[e].v == u)
			deg_u++;
	}
	return deg_u;
}

void neighbours(Graph *pG, int u){
	printf("Neighbour[%d] = ", u);
	for(int v = 1; v <= pG->n; v++){
		if(adjacent(pG, u, v))
			printf("%d ", v);
	}
	printf("\n");
}

int main(){
	freopen("dt.txt", "r", stdin);
	int n, m;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(int i = 0; i < G.m; i++){
		printf("%d %d\n", G.edges[i].u,G.edges[i].v);
	}
	
	for(int i = 1; i <= G.n; i++){
		printf("degree[%d] = %d\n", i, degree(&G, i));
	}
	for(int u = 1; u <= G.n; u++) {
		neighbours(&G, u);
	}
	return 0;
}
