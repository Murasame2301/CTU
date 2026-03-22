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
	pG->A[u][v]++;
	pG->m++;
}
int mark[MAX_N];
int parent[MAX_N];
int has_circle, start, end;
void DFS(Graph *pG, int u, int p){
    parent[u] = p;
	mark[u] = 1;
	for(int v = 1; v <= pG->n; v++)
		if(pG->A[u][v]){
			if (!mark[v])
				DFS(pG, v, u);
			else if(mark[v] == 1){
                start = v;
                end = u;
				has_circle = 1;
            }
		}
	mark[u] = 2;
}

int main(){
 	//freopen("dt.txt", "r", stdin);
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	Graph G;
	init_graph(&G, n);
	for (int i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	has_circle = 0;
	for(u = 1; u <= G.n; u++)
		if(!mark[u])
			DFS(&G, u, -1);
	if(has_circle) {
		List L; make_null(&L);
        push_back(&L, start);
        while (end != start){
            push_back(&L, end);
            end = parent[end];
        }
        push_back(&L, start);
        for(int i = L.size; i >= 1; i--){
            printf("%d ", element_at(&L, i));
        }
        
	}
	else printf("-1");
	return 0;
}
