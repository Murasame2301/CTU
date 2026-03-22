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
        if (adjacent(G, i, x)) //adjacent(G, i, x)
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
//Khai bao cau truc cua Ngan xep
typedef struct {
    int data[MAX_Element];
    int size;
}Stack;

//Khoi tao ngan xep rong
void make_null_stack(Stack *stack) {
    stack->size = 0;
}

//Them mot phan tu vao ngan xep
void push_stack(Stack *stack, int x) {
    stack->data[stack->size] = x;
    stack->size++;
}

//Lay mot phan tu trong Stack
int top(Stack *stack) {
    return stack->data[stack->size-1];
}

//Xoa mot phan tu thuoc Stack
void pop(Stack *stack) {
    stack->size--;
}

//Kiem tra Stack co rong hay khong
int empty(Stack *stack) {
    return stack->size == 0;
}
void depth_first_search(Graph *G, int x) {
    Stack S;
    make_null_stack(&S);
    push_stack(&S, x);
    //Khoi tao ta ca cac dinh chua duoc duyet
    int mark[MAX_Vertices];
    int i, j;
    for(i=1; i<=G->n; i++)
        mark[i]=0;
    while(!empty(&S)) {
        int u = top(&S);
        pop(&S);
        if(mark[u] == 1)
            continue;
        printf("Duyet: %d\n", u);
        mark[u] = 1;
        List list = neighbors(G, u);
        for(i=1; i<=list.size; i++) {
            int v = element_at(&list, i);
            if(mark[v] == 0)
                push_stack(&S, v);
        }
    }
}

int main() {
    Graph G;
    freopen("DFS.txt", "r", stdin);
    int n, m;
    scanf("%d%d",&n,&m);
    init_Graph(&G, n);
    int e, u, v;
    for(e=1; e<=m; e++){
        scanf("%d%d",&u,&v);
        add_edge(&G, u, v);
    }
    depth_first_search(&G,1);
    return 0;
}
