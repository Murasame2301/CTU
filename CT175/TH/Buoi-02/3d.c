#include <stdio.h>
#define MAX_N 100
typedef struct{
	int data[MAX_N];
	int top_idx;
} Stack;

void make_null_stack(Stack *pS){
	pS->top_idx = -1;
}

int empty(Stack *pS){
	return pS->top_idx == -1;
}

void push(Stack *pS, int x){
	pS->top_idx++;
	pS->data[pS->top_idx] = x;
}

int top(Stack *pS){
	return pS->data[pS->top_idx];
}

void pop(Stack *pS){
	pS->top_idx--;
}

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
	push_back(&pG->adj[u],v);
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

void DFS(Graph *pG, int s){
	Stack S; make_null_stack(&S);
	push(&S, s);
	while (!empty(&S)){
		int u = top(&S);
		pop(&S);
		if (mark[u])
			continue;
		printf("%d\n", u);
		mark[u] = 1;
		for(int v = 1; v <=pG->n; v++)
			if(adjacent(pG, u, v))
				push(&S, v);
	}
}

int main(){
//	freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m, u, v, e, s;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
		
	for (e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}
	scanf("%d", &s);
	DFS(&G, s);
	return 0;
}
