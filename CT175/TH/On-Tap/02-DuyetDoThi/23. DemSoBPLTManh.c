#include <stdio.h>
#define MAX_N 100
typedef struct{
	int data[MAX_N];
	int size;
} List;

void make_null_list(List *pL){
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
	int data[MAX_N];
	int idx;
} Stack;

void make_null_stack(Stack *pS){
	pS->idx = -1;
}

void push(Stack *pS, int x){
	pS->data[++pS->idx] = x;
}

void pop(Stack *pS){
	pS->idx--;
}

int top(Stack *pS){
	return pS->data[pS->idx];
}

int empty(Stack *pS){
	return pS->idx == -1;
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

int min(int x, int y){
	if(x < y) return x;
	return y;
}

Stack S; 
int cnt, scc_cnt;
int num[MAX_N], min_num[MAX_N];
int on_stack[MAX_N] ={0};
void SCC(Graph *pG, int u){
	num[u] = min_num[u] = ++cnt;
	push(&S, u);
	on_stack[u] = 1;
	for(int v = 1; v <= pG->n; v++){
		if(pG->A[u][v]){
			if(num[v] < 0){
				SCC(pG, v);
				min_num[u] = min(min_num[u], min_num[v]);
			}
			else if(on_stack[v]){
				min_num[u] = min(min_num[u], num[v]);
			}
		}
	}
	if (num[u] == min_num[u]){
			scc_cnt++;
			int w;
			do {
				w = top(&S);
				pop(&S);
				on_stack[w] = 0;
			} while (w != u);
	}
}

int main(){
// 	freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u,&v);
		add_edge(&G, u, v);
	}
	for(int u = 1; u <= G.n; u++)
		num[u] = -1;
	make_null_stack(&S);
	for(int u = 1; u <= G.n; u++)
		if(num[u] == -1){
			SCC(&G, u);
		}
    printf("%d", scc_cnt);
	return 0;
}
