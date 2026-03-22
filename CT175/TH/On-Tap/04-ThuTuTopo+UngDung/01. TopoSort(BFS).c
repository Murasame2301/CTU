#include <stdio.h>
#define MAX_N 100

typedef struct{
	int size;
	int data[MAX_N];
}List;

void make_null_list(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size++] = x;
}

int element_at(List *pL, int p){
	return pL->data[p-1];
}

typedef struct{
	int front, rear;
	int data[MAX_N];
}Queue;

void make_null_queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

void enqueue(Queue *pQ, int x){
	pQ->data[++pQ->rear] = x;
}

void dequeue(Queue *pQ){
	pQ->front++;
}

int front(Queue *pQ){
	return pQ->data[pQ->front];
}

int empty_queue(Queue *pQ){
	return pQ->front > pQ->rear;
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
	pG->A[u][v] = 1;
}

int d[MAX_N];
void topo_sort(Graph *pG, List *pL){
	for(int u = 1; u <= pG->n; u++){
		for(int v = 1; v <= pG->n; v++)
			if(pG->A[v][u])
				d[u]++;
	}
	Queue Q;
	make_null_queue(&Q);
	
	for(int u = 1; u <= pG->n; u++)
		if(d[u] == 0)
			enqueue(&Q, u);
			
	make_null_list(pL);
	
	while(!empty_queue(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		for(int v = 1; v <= pG->n; v++)
			if(pG->A[u][v]){
				d[v]--;
				if(d[v] == 0)
					enqueue(&Q, v);
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
	List L;
	topo_sort(&G, &L);
	for(int p = 1; p <= L.size; p++){
		printf("%d ", element_at(&L, p));
	}
	return 0;
}
