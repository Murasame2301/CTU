#include <stdio.h>
#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_Element 40
typedef struct {
    int A[MAX_Vertices][MAX_Vertices];
    int n; //so luong dinh
}Graph;

void init_Graph(Graph *G, int n) {
    int i, j;
    G->n = n;
    for (i=1; i <=G->n; i++)//dong cua ma tran
        for (j=1; j<=G->n; j++) //cot cua ma tran
            G->A[i][j] = 0;  
}

//Them cung vao do thi
void add_edge(Graph *G, int x, int y) {
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}
//Kiem tra dinh x va dinh y co phai la lang gieng cua nhau hay khong
int adjacent(Graph *G, int x, int y) {
    return (G->A[x][y] != 0);
}

//Tinh bac cua dinh x trong do thi
int degree(Graph *G, int x) {
    int deg = 0, i;
    for (i=1; i<=G->n; i++)
        if (G->A[i][x] == 1) //Ton tai cung
            deg++;
    return deg;
}
//Khai bao cau truc danh sach List
typedef struct {
    int data[MAX_Length];
    int size;
}List;

//Ham khoi tao danh sach rong
void make_null(List *list) {
    list->size = 0;
}

//Them mot phan tu (dinh) vao cuoi danh sach
void push_back(List *list, int x) {
    list->data[list->size] = x;
    list->size++;
}

//Lay mot phan tu (dinh) trong danh sach tai vi tri i
int element_at(List *list, int i) {
    return list->data[i-1];
}

//Tim lang gieng cua dinh x
List neighbors(Graph *G, int x) {
    List L;
    make_null(&L);
    int i;
    for(i=1; i<=G->n; i++) {
        if(G->A[i][x] == 1)
            push_back(&L, i);
    }
    return L;
}
//Khai bao cau truc Hang doi (Queue)
typedef struct{
	int data[MAX_Element];
	int front;//Chi so dau hang doi
	int rear;//Chi so o cuoi hang doi
}Queue;

//Khoi tao hang doi rong
void make_null_Queue(Queue *Q) {
	Q->front = 0;
	Q->rear = -1;
}

//Them mot phan tu vao trong hang doi
void push_Queue(Queue *Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}

//Kiem tra hang doi co rong hay ko?
int empty_Queue(Queue *Q) {
	return Q->front > Q->rear;
}

//Lay mot phan tu o dau hang doi
int top(Queue *Q) {
	return Q->data[Q->front];
}

//Xoa phan tu o dau hang doi
void pop(Queue *Q){
	Q->front++;
}

void breath_first_search(Graph *G){
	Queue Q;
	make_null_Queue(&Q);
	int mark[MAX_Vertices];
	int i;
	for(i=1; i<=G->n; i++)
		mark[i] = 0;
	push_Queue(&Q, 1);
	while(!empty_Queue(&Q)) {
		int u = top(&Q);
		pop(&Q);
		if (mark[u] == 1)
			continue;
		printf("Duyet: %d\n",u);
		mark[u]=1;
		List L;
		make_null(&L);
		L = neighbors(G,u);
		int v;
		for(i=1; i<=L.size; i++){
			v = element_at(&L, i);
			if(mark[v] == 0)
				push_Queue(&Q, v);
		}
	}
}

int main() {
	Graph G;
	freopen("BFS_data.txt","r",stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int e, x, y;
	for(e=1; e<=m; e++){
		scanf("%d%d", &x, &y);
		add_edge(&G, x, y);
	}
	breath_first_search(&G);
}
