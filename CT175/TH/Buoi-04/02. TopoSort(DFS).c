#include <stdio.h>
#define MAX_N 100

typedef struct{
	int size;
	int data[MAX_N];
}List;

void make_null_list(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size++] = x;
}

int element_at(List *pL, int p){
	return pL->data[p-1];
}

typedef struct{
	int n,m;
	int A[MAX_N][MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
}

int d[MAX_N], mark[MAX_N];
void topo_sort(Graph *pG, int u, List *pL){
	mark[u] = 1;
	for(int v = 1; v <= pG->n; v++)
		if(pG->A[u][v] && !mark[v]){
			topo_sort(pG, v, pL);
			d[v]--;
		}
	push_back(pL, u);			
}

void reverse_List(List *pL){
	for(int i = 0; i < pL->size/2; i++){
		int tmp = pL->data[i];
		pL->data[i] = pL->data[pL->size- i - 1];
		pL->data[pL->size - i - 1] = tmp;
	}
}


int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	Graph G;
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	List L;
	make_null_list(&L);
	for(int u = 1; u <= n; u++)
		if(!mark[u])
			topo_sort(&G, u, &L);
	reverse_List(&L);
	for(int p = 1; p <= L.size; p++){
		printf("%d ", element_at(&L, p));
	}
	return 0;
}
