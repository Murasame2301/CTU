//Do thi co huong
#include <stdio.h> 
#define MAX_M 500 
typedef struct {
	int u, v; 
} Edge; 
 
typedef struct { 
	int n, m; 
	Edge edges[MAX_M]; 
} Graph; 

void init_graph(Graph *pG, int n) { 
	pG->n = n; 
	pG->m = 0; 
} 

void add_edge(Graph *pG, int u, int v) {
    int i;
    for(i = 0; i < pG->m; i++)
	    if (pG->edges[i].u == u && pG->edges[i].v == v)
		    return;
	if (u >= 1 && v >= 1 && u <= pG->n && v <= pG->n) {
		pG->edges[pG->m].u = u;
		pG->edges[pG->m].v = v;
		pG->m++;
	}
}

int adjacent(Graph *pG, int u, int v) { 
	int e; 
	for (e = 0; e < pG->m; e++) 
	if ((pG->edges[e].u == u && pG->edges[e].v == v)) 
	 	return 1;
	return 0; 
}

int main() { 
	Graph G;
	init_graph(&G, 3);
	add_edge(&G, 1, 3);
	add_edge(&G, 2, 3);
	add_edge(&G, 2, 2);
	printf("n = %d, m = %d\n", G.n, G.m); 
	int i, j; 
	for (i = 1; i <= G.n; i++)
		for(j = 1; j <= G.n; j++)
			if (adjacent(&G, i, j))
				printf("%d ke voi %d.\n", i, j);
			else
				printf("%d KHONG ke voi %d.\n", i, j);
	return 0; 
}
