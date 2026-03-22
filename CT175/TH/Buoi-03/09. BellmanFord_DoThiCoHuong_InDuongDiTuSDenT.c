#include <stdio.h>
#define MAX_N 500
#define MAX_M 1000
#define oo 10000000
typedef struct{
	int u, v, w;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAX_N];
}Graph;


void init_graph(Graph *pG, int n, int m){
	pG->m = 0;
	pG->n = n;
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].w = w;
	pG->m++;
}

int p[MAX_N], mark[MAX_N], pi[MAX_N];

void BellmanFord(Graph *pG, int s){
	for(int u = 1; u <= pG->n; u++){
		pi[u] = oo;
	}
	pi[s] = 0;
	p[s] = -1;
	int u, v, w;
	for(int it = 1; it < pG->n; it++){
		for(int k = 0; k < pG->m; k++){
			u = pG->edges[k].u;
			v = pG->edges[k].v;
			w = pG->edges[k].w;
			if(pi[u] == oo)
				continue;
			if(pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
}

int path[MAX_N], length;
void find_Short_Path(Graph *pG, int s, int t){
	int end = t, idx = 0;
	while (s != end){
		path[idx++] = end;
		end = p[end];
	}
	path[idx] = s;
	length = idx;
}

int main(){
	int n,m;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n,m);
	
	for(int i = 0; i < m; i++){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int s, t;
	scanf("%d%d", &s, &t);
	BellmanFord(&G, s);
	find_Short_Path(&G, s, t);
	for(int i = length; i >= 0; i--){
		if(i != 0){
			printf("%d -> ", path[i]);
		}
		else printf("%d", path[i]);
	}
	return 0;
}
