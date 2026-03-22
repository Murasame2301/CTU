#include <stdio.h>
#define MAX_Vertices 20
#define MAX_Length 20
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

void add_edge(Graph *G, int x, int y) {
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}
//Kiem tra dinh x va dinh y co phai lang gieng cua nhau hay khong
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

//Them mot phan tu (dinh vao cuoi danh sach)
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

int main() {
    Graph G;
    //Khoi tao do thi
    freopen("dothi.txt", "r", stdin);
    int n, m;//n - so luong dinh; m - so luong cung
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, e;
    for(e=1; e<=m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    int i, j;
    for (i=1; i<=G.n; i++){
        printf("degree(%d)= %d\n",i, degree(&G, i));
    }
    //Can tim lang gieng cua dinh 4
    printf("\nIn ra danh sach lang gieng cua cua cac dinh trong do thi\n");
    for (i=1; i<=G.n;i++){
        List list = neighbors(&G, i);
        printf("Neighbors(%d) = [", i);
        for(j=1; j<=list.size; j++)
            printf("%d ", element_at(&list,j));
        printf("]\n");
    }
    // //In ra lang gieng cua dinh 4
    // for (i=1; i<=L.size; i++)
    //     printf("\n%d", element_at(&L, i));
    return 0;
}