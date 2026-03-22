#include <stdio.h>
#define MAX_N 100
typedef struct {
	int data[MAX_N];
	int size;
}List;

void make_null_List(List *pL){
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
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	for(int i = 1; i <= n; i++){
		make_null_List(&pG->adj[i]);
	}
}

void add_edge(Graph *pG, int u, int v){
	if (u!=v){
		push_back(&pG->adj[u], v);
		push_back(&pG->adj[v], u);
	}
	else push_back(&pG->adj[u], v);
}

int adjacent(Graph *pG, int u, int v){
	for(int i = 1; i <= pG->adj[u].size; i++){
		if(v == element_at(&pG->adj[u], i))
			return 1;
	}
	return 0;
}

void neighbours(Graph *pG, int u){
	printf("neighbour[%d] = ", u);
	for(int i = 1; i <= pG->adj[u].size; i++){
		printf("%d ", element_at(&pG->adj[u], i));
	}
	printf("\n");
}

int degree(Graph *pG, int u){
	return pG->adj[u].size;
}

int main(){
	freopen("dt.txt", "r", stdin);
	int n,m;
	scanf("%d%d", &n, &m);
	Graph G;
	init_graph(&G, n);
	for(int i = 0; i <m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(int i = 1; i <= n; i++){
		printf("%d: ", i);
		for(int j = 1; j <= G.adj[i].size; j++){
			printf("%d ", element_at(&G.adj[i], j));
		}
		printf("\n");
	}
	for(int i = 1; i <= n; i++){
		neighbours(&G, i);
	}
	return 0;
}
