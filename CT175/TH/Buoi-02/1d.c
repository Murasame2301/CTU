#include <stdio.h>
#define MAX_SIZE 100
#define MAX_N 100
typedef struct{
	int data[MAX_SIZE];
	int front, rear;
} Queue;

void make_null_queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

void enqueue(Queue *pQ, int u){
	pQ->rear++;
	pQ->data[pQ->rear] = u;
}

int front(Queue *pQ){
	return pQ->data[pQ->front];
}

void dequeue(Queue *pQ){
	pQ->front++;
}

int empty(Queue *pQ){
	return pQ->front > pQ->rear;
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

int count_list(List *pL){
	return pL->size;
}

typedef struct{
	int n, m;
	List adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i;
	for(i = 1; i <= n; i++)
		make_null(&pG->adj[i]);
}

void add_edge(Graph *pG, int u, int v){
	push_back(&pG->adj[u], v);
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

void BFS(Graph *pG, int s){
	Queue Q;
	make_null_queue(&Q);
	enqueue(&Q, s);
	while (!empty(&Q)){
		int u = front(&Q); dequeue(&Q);
		if(mark[u])
			continue;
		printf("%d\n", u);
		mark[u] = 1;
		int v;
		for(v = 1; v <= pG->n; v++)
			if(adjacent(pG, u, v))
				enqueue(&Q, v);
	}
}

int main() {
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n,m, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 0; e < m; e++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int s; scanf("%d", &s);
	BFS(&G, s);
	return 0;
}
