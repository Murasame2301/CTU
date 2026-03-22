#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
#define MAX_M 500
typedef struct{
	int n, m;
	int A[MAX_N][MAX_M];
} Graph;

void init_graph(Graph *pG, int n, int m){
	int u, e;
	pG->n = n;
	pG->m = m;
	for (u = 1; u <= n; u++)
    	for (e = 1; e <= m; e++)
					pG->A[u][e] = 0;
}

void add_edge(Graph *pG, int u, int v, int e) {
	pG->A[u][e] = 1;
	pG->A[v][e] = 1;
}

int adjacent(Graph *pG, int u, int v) {
	int e;
	for (e = 1; e <= pG->m; e++)
	if (pG->A[u][e] == 1 && pG->A[v][e] == 1)
		return 1;
	return 0;
}

int degree(Graph *pG, int u) {
	int e, deg_u = 0;
	for (e = 1; e <= pG->m; e++)
    if (pG->A[u][e] == 1)
		deg_u++;
	return deg_u;
}

int main() {
	Graph G;
    int n = 4, m = 5, u, e; 
    init_graph(&G, n, m);

    add_edge(&G, 1, 1, 2);
    add_edge(&G, 2, 1, 3);
    add_edge(&G, 3, 1, 4);
    add_edge(&G, 4, 2, 3);
    add_edge(&G, 5, 3, 4);

    printf("Ma tran dinh - canh:\n");
    for (u = 1; u <= n; u++) {
        for (e = 1; e <= m; e++)
            printf("%d ", G.A[u][e]);
        printf("\n");
    }

    printf("adjacent(1,2) = %d\n", adjacent(&G, 1, 2));
    printf("adjacent(2,4) = %d\n", adjacent(&G, 2, 4));

    for (u = 1; u <= n; u++)
        printf("degree(%d) = %d\n", u, degree(&G, u));

    return 0;
}
