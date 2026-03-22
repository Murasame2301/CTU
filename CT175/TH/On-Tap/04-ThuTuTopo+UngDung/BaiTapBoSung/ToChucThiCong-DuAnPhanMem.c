#include <stdio.h>
#define MAX_N 100
#define oo 100000
#define max(x,y) (x > y)?(x):(y)
#define min(x,y) (x > y)?(y):(x)

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
	pG->A[u][v]++;
}

int indeg[MAX_N];
void topo_sort(Graph *pG, List *pL){
	for(int u = 1; u <= pG->n; u++){
		for(int v = 1; v <= pG->n; v++)
			if(pG->A[v][u])
				indeg[u]++;
	}
	Queue Q;
	make_null_queue(&Q);
	
	for(int u = 1; u <= pG->n; u++)
		if(indeg[u] == 0)
			enqueue(&Q, u);
			
	make_null_list(pL);
	
	while(!empty_queue(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		for(int v = 1; v <= pG->n; v++)
			if(pG->A[u][v]){
				indeg[v]--;
				if(indeg[v] == 0)
					enqueue(&Q, v);
			}
	}
}

int d[MAX_N];
int main(){
	int n, v; Graph G;
	scanf("%d", &n);
	init_graph(&G, n+2);
	int alpha = n + 1; int beta = n+2;
	for(int u = 1; u <= n; u++){
		scanf("%d", &d[u]);
		do{
			scanf("%d", &v);
			if(v > 0)
				add_edge(&G, v, u);
		} while (v > 0);
	}
	
	for(int u = 1; u <= n; u++){ 
		int deg_neg = 0;
		for(int x = 1; x <= n; x++){
			if (G.A[x][u]){
				deg_neg++;
			}
		}
		if(deg_neg == 0){
			add_edge(&G, alpha, u);
		}
	}
	
	for(int u = 1; u <= n; u++){
		int deg_pos = 0;
		for(int v = 1; v <= n; v++){
			if(G.A[u][v]){
				deg_pos++;
			}
		}
		if(deg_pos == 0)
			add_edge(&G, u, beta);
	}
	     
	List L;
	topo_sort(&G, &L);

	int t[MAX_N];
	t[alpha] = 0;
	
	for(int j = 2; j <= L.size; j++){
		int u = element_at(&L, j);
		t[u] = -oo;
		for(int x = 1; x <= G.n; x++){
			if (G.A[x][u]){
				t[u] = max(t[u], t[x] + d[x]);
			}
		}
	}
	
	int T[MAX_N];
	T[beta] = t[beta];
	
	for(int j = L.size - 1; j >= 1; j--){
			int u = element_at(&L, j);
			T[u] = +oo;
			for(int v = 1; v <= G.n; v++)
				if(G.A[u][v]){
					T[u] = min(T[u], T[v] - d[u]);
				}
	}
	
	int p, q;
	scanf("%d%d", &p, &q);
	if(q > t[p] && q < T[p])
		printf("YES");
	else printf("NO");
	return 0;
}
