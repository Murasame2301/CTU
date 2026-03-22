#include <stdio.h>
#define MAX_N 100

typedef struct{
	int data[MAX_N];
	int size;
} List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int p){
	return pL->data[p-1];
}

typedef struct{
	int n;
	List adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
}

void add_edge(Graph *pG, int u, int v){
	push_back(&pG->adj[u],v);
}

int adjacent(Graph *pG, int u, int v){
	int i;
	for(i = 1; i <= pG->adj[u].size; i++) {
		if (element_at(&pG->adj[u], i) == v)
			return 1;
	}
	return 0;
}

int mark[MAX_N];
int parent[MAX_N];

void DFS(Graph *pG, int u, int p){
	mark[u] = 1;
	parent[u] = p;
	for(int v = 1; v <= pG->n; v++){
		if(adjacent(pG, u, v) && mark[v] == 0)
			DFS(pG, v, u);
	}
}

int main() {
	freopen("dt.txt", "r", stdin);
	Graph G;
	int i, n,m, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 0; e < m; e++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(int i = 0; i <= G.n; i++)
		parent[i] = -1;
	for(int i = 1; i <= n; i++)
		if (!mark[i])
			DFS(&G, i, -1);
	for(i=1; i<=G.n; i++)
		printf("%d %d\n", i, parent[i]);
	return 0;
}
