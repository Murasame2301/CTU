#include <stdio.h>
#define MAX_N 100
#define MAX_ELEMENTS 100

typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} List;

void make_null(List *pL) {
	pL->size = 0;
}

void push_back(List *pL, int x) {
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int i) {
	return pL->data[i-1];
}

int count_list(List *pL) {
	return pL->size;
}

typedef struct {
	int n;
	List adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
	int u;
	pG->n = n;
	
	for (u = 1; u <= n; u++)
		make_null(&pG->adj[u]);

}

/*
//Them cung (u, v) vao don do thi vo huong
void add_edge(Graph *pG, int u, int v) {
	push_back(&pG->adj[u], v);
	push_back(&pG->adj[v], u);
}
*/


/*
//Them cung (u, v) vao da do thi vo huong
void add_edge(Graph *pG, int u, int v) {
	if (u != v) {
		push_back(&pG->adj[u], v);
		push_back(&pG->adj[v], u);
	}
	else push_back(&pG->adj[u],v);
}
*/


//Them cung (u, v) vao do thi co huong
void add_edge(Graph *pG, int u, int v) {
	push_back(&pG->adj[u], v);
}

//Kiem tra u co ke voi v khong (do thi vo huong)
int adjacent(Graph *pG, int u, int v) {
	int j;
	for (j = 1; j <= pG->adj[u].size; j++)
		if (element_at(&pG->adj[u], j) == v)
			return 1;
	return 0;
}

//Do thi co huong
int indegree(Graph *pG, int x) {
	int i,j, indeg_v = 0;
	for(i = 1; i <= pG->n; i++){
		//if(adjacent(pG, i, x)) indeg_v++;
		for(j = 1; j <= pG->adj[i].size; j++)
			if(element_at(&pG->adj[i], j) == x)
				indeg_v++;
	}
	return indeg_v;
}

int outdegree(Graph *pG, int x) {
	return pG->adj[x].size;
}

int degree(Graph *pG, int x){
	return indegree(pG,x) + outdegree(pG,x);
}

/*
//Do thi vo huong
int indegree(Graph *pG, int x) {
	int i,j, indeg_v = 0;
	for(i = 1; i <= pG->n; i++){
		//if(adjacent(pG, i, x)) indeg_v++;
		for(j = 1; j <= pG->adj[i].size; j++)
			if(element_at(&pG->adj[i], j) == x)
				indeg_v++;
	}
	return indeg_v;
}

int outdegree(Graph *pG, int x) {
	return pG->adj[x].size;
}

int degree(Graph *pG, int x){
	return pG->adj[x].size;;
}
*/


int main() {
	Graph G;
	int n,m, i, u;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	int e;
	for(e = 0; e < m; e++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	//Liet ke cac dinh ke
	for(e = 1; e <= n; e++) {
		printf("%d: ", e);
		for(i = 1; i <= count_list(&G.adj[e]); i++)
			printf("%d ", element_at(&G.adj[e], i));
		printf("\n");
	}
	for (u = 1; u <= n; u++) {
		printf("deg_in(%d) = %d\n", u, indegree(&G, u));
	}
	
	for (u = 1; u <= n; u++) {
		printf("deg_out(%d) = %d\n", u, outdegree(&G, u));
	}
	
	for (u = 1; u <= n; u++) {
		printf("degree(%d) = %d\n", u, degree(&G, u));
	}
}


