#include <stdio.h>
#define MAX_N 100

typedef struct{
	int data[MAX_N], front, rear;
} Queue;

void make_null_queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

int empty_Queue(Queue *pQ){
	return pQ->front > pQ->rear;
}

void enqueue(Queue *pQ, int x){
	pQ->data[++pQ->rear] = x;
}

int top(Queue *pQ){
	return pQ->data[pQ->front];
}

void pop(Queue *pQ){
	pQ->front++;
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
void BFS(Graph *pG, int s, int p){
	Queue Q; make_null_queue(&Q);
	enqueue(&Q, s);
	while(!empty_Queue(&Q)){
		int u = top(&Q); pop(&Q);
		if(mark[u]) continue;
		mark[u] = 1;
		for(int v = 1; v <= pG->n; v++){
			if(pG->A[u][v] && !mark[v]){
				enqueue(&Q, v);
				if(parent[v] == -1)
					parent[v] = u;
			}
		}
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
	for(int i = 1; i <= n; i++){
		parent[i] = -1;
	}
	for(int i = 1; i <= n; i++){
		if(!mark[i])
			BFS(&G, i, -1);
	}
	for(int i = 1; i <= n; i++){
		printf("%d %d\n", i, parent[i]);
	}
	return 0;
}
