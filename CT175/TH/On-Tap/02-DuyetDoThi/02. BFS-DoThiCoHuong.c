#include <stdio.h>
#define MAX_N 100

typedef struct{
	int data[MAX_N];
	int front, rear;
}Queue;

void make_null_Queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

void enqueue(Queue *pQ, int x){
	pQ->rear++;
	pQ->data[pQ->rear] = x;
}

int empty_Queue(Queue *pQ){
	return pQ->front > pQ->rear;
}

int top(Queue *pQ){
	return pQ->data[pQ->front];
}

void pop(Queue *pQ){
	pQ->front++;
}
typedef struct{
	int A[MAX_N][MAX_N];
	int n, m;
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

int adjacent(Graph *pG, int u, int v){
	if(pG->A[u][v] != 0)
		return 1;
	return 0;
}


int mark[MAX_N];
void BFS(Graph *pG, int s){
	Queue Q; make_null_Queue(&Q);
	enqueue(&Q, s);
	while(!empty_Queue(&Q)){
		int u = top(&Q); pop(&Q);
		if(mark[u]) continue;
		printf("%d\n", u);
		mark[u] = 1;
		for(int v = 1; v <= pG->n; v++){
			if(adjacent(pG, u, v))
				enqueue(&Q, v);
		}
	}
}
int main(){
	int n, m;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(int u = 1; u <= n; u++){
		if(!mark[u])
			BFS(&G,u);
	}
	return 0;
}
