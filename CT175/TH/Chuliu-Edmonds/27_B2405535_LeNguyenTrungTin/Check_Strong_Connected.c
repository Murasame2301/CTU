#include <stdio.h>
#define MAXN 100
#define MAXM 500
#define MAXIT 10
#define INF 9999999

typedef struct {
    int u, v, w;
    int link;
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAXM];
} Graph;

typedef struct {
    int n;
    int parent[MAXN];
    int weight[MAXN];
    int link[MAXN];
} Tree;

void init_graph(Graph *G, int n) {
    G->n = n;
    G->m = 0;
}

void init_tree(Tree *T, int n) {
    T->n = n;
    int i;
    for (i = 1; i <= n; i++) {
        T->parent[i] = -1;
        T->weight[i] = INF;
        T->link[i]   = -1;
    }
}

void add_edge(Graph *G, int u, int v, int w, int link) {
    int m = G->m;
    G->edges[m].u = u;
    G->edges[m].v = v;
    G->edges[m].w = w;
    G->edges[m].link = link;
    G->m++;
}

int visited[MAXN];
void dfs(Graph *G, int u){
	visited[u] = 1;
	for(int e = 0; e < G->m; e++){
		if(G->edges[e].u == u){
			int v = G->edges[e].v;
			if(!visited[v]){
				dfs(G, v);
			}
		}
	}
}

int isStrongConnected(Graph *pG){
	dfs(pG, 1);
	for(int i = 1; i <= pG->n; i++){
		if(!visited[i])
			return 0;
	}
	return 1;
}

int main() {
    Graph G;
    int n, m, i, e, u, v, w;

    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (e = 0; e < m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w, -1);
    }
	if (isStrongConnected(&G)){
		printf("Yes\n");
	}
	else printf("No\n");
    return 0;
}
