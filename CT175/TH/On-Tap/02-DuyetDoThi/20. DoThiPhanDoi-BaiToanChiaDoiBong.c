#include <stdio.h>
#define MAX_N 100

typedef struct 
{
    int data[MAX_N];
    int size;
} List;

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
	if(u != v){
		pG->A[u][v]++;
		pG->A[u][v]++;
	}
	else pG->A[u][v]++;
}

int color[MAX_N];// -1 có nghia là chua tô màu (chua tham); 0 và 1 là hai màu trái ngu?c nhau
int conflict;
void DFS_CheckBipartite(Graph *pG, int u, int cl){
    color[u] = cl;
    for(int v = 1; v <= pG->n; v++){
        if(pG->A[u][v]){
            if(color[v] == -1)
                DFS_CheckBipartite(pG, v, 1 - cl);
            else if(color[v] == color[u])
                conflict = 1;
        }
    }
}

int main(){
    // freopen("dt.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    for(int i = 0; i< m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
   conflict = 0;
   for(int u = 1; u <= n; u++)
        color[u] = -1;
   
   for(int u = 1; u <= n; u++)
        if(color[u] == -1)
            DFS_CheckBipartite(&G, u, 0);
    if(conflict)
        printf("IMPOSSIBLE");
    else {
        for(int u = 1; u <= n; u++)
            if(color[u] == 0) printf("%d ", u);
        printf("\n");
        for(int u = 1; u <= n; u++)
            if(color[u] == 1) printf("%d ", u);
    }
    return 0;
}
