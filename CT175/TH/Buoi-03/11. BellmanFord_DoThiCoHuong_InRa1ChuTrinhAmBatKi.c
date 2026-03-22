#include <stdio.h>
#define MAX_N 500
#define MAX_M 1000
#define oo 10000000
typedef struct{
	int u, v, w;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAX_M];
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

int p[MAX_N], mark[MAX_N], pi[MAX_N], negative_cycle;
int cycle_len, cycle[MAX_N];
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
    int x = -1;
    for(int k = 0; k < pG->m; k++){
        int u = pG->edges[k].u;
        int v = pG->edges[k].v;
        int w = pG->edges[k].w;
        if(pi[u] == oo) continue;
        if(pi[u] + w < pi[v]){
            p[v] = u;                          
            x = v;
            negative_cycle = 1;
            break;
        }
    }
    if(!negative_cycle) return;

	for(int i = 1; i <= pG->n; i++){
	    x = p[x];
	    if (x == -1) {
			negative_cycle = 0;
			cycle_len = 0;
			return;
		}
	}
    
    int cur = x;
    do{
        cycle[cycle_len++] = cur;
        cur = p[cur];
    } while(cur != x);

    cycle[cycle_len++] = x; 
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
	int s;
	scanf("%d", &s);
	BellmanFord(&G, s);
	if(negative_cycle) {
	    printf("YES\n");
	    for(int i = 0; i < cycle_len; i++){
	        printf("%d", cycle[i]);
	        if(i < cycle_len - 1) printf(" -> ");
	    }
	}
	else printf("NO");
	return 0;
}
