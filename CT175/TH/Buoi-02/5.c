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
	if (u != v){
		push_back(&pG->adj[u], v);
		push_back(&pG->adj[v], u);
	}
	else push_back(&pG->adj[u],v);
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

void DFS(Graph *pG, int u){
	if(mark[u])
		return;
	printf("%d\n", u);
	mark[u] = 1;
	for(int i = 1; i <= pG->adj[u].size; i++){
		int v = element_at(&pG->adj[u], i);
		DFS(pG, v);
	}
}

int main(){
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m, u, v, e, s;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
		
	for (e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}
	scanf("%d", &s);
	//Duyet tu dinh 1
//	DFS(&G, 1);
	//Duyet tu dinh s
//	DFS(&G, s);
	//Duyet toan bo do thi
	for(int i = 1; i <= G.n; i++)
		if (!mark[i])
			DFS(&G, i);
	return 0;
}
