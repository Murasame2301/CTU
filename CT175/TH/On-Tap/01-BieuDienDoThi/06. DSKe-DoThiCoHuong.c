#include <stdio.h>
#define MAX_N 100

typedef struct{
	int data[MAX_N], size;
} List;

void make_null_list(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int p){
	return pL->data[p-1];
}

typedef struct {
	int n;
	List adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	for(int i = 1; i <= n; i++)
		make_null_list(&pG->adj[i]);
}

void add_edge(Graph *pG, int u, int v){
	push_back(&pG->adj[u], v);
}

int adjacent(Graph *pG, int u, int v){
	for(int i = 1; i <= pG->adj[u].size; i++){
		if(element_at(&pG->adj[u], i) == v)
			return 1;
	}
	return 0;
}

int indegree(Graph *pG, int u){
	int indeg_u = 0;
	for(int i = 1; i <= pG->n; i++){
		List L = pG->adj[i];
		for(int j = 1; j <= L.size; j++)
			if(element_at(&L, j) == u)
				indeg_u++;
	}
	return indeg_u;
}
int outdegree(Graph *pG, int u){
	return pG->adj[u].size;
}
int degree(Graph *pG, int u){
	return indegree(pG, u) + outdegree(pG, u);
}

void neighbours(Graph *pG, int u){
	printf("neighbour[%d] = ", u);
	for(int i = 1; i <= pG->adj[u].size; i++){
		printf("%d ", element_at(&pG->adj[u], i));
	}
	printf("\n");
}

int main(){
	freopen("dt.txt", "r", stdin);
	int n, m;
	Graph G;
	scanf("%d%d", &n,&m);
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(int i = 1; i <= n; i++){
		neighbours(&G, i);
	}
	
	for(int i = 1; i <= n; i++){
		printf("degree(%d) = %d + %d = %d\n", i,indegree(&G, i), outdegree(&G, i), degree(&G, i));
	}
}
