#include <stdio.h>
#define MAX_N 100

typedef struct{
	int n, m;
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
	pG->A[v][u]++;
}

int max(int x, int y){
	if(x > y) return x;
	else return y;
}
int mark[MAX_N];
int cnt_v;
void DFS(Graph *pG, int u){
	if(mark[u]) return;
	cnt_v++;
	mark[u] = 1;
	for(int v = 1; v <= pG->n; v++)
		if(pG->A[u][v])
			DFS(pG, v);
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
	int res = 0;
	for(int i = 1; i <= n; i++){
		if(!mark[i]){
			cnt_v = 0;
			DFS(&G, i);
			res = max(res, cnt_v);
		}
	}
	printf("%d", res);
	return 0;
}
