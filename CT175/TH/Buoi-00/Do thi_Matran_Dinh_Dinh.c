#include <stdio.h>
#define MAX_Vertices 20
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
int main() {
    Graph G;
    //Khoi tao do thi
    init_Graph(&G, 6);
    add_edge(&G, 2, 6);
    add_edge(&G, 6, 4);
    add_edge(&G, 5, 6);
    add_edge(&G, 1, 4);
    add_edge(&G, 1, 5);
    add_edge(&G, 2, 3);
    add_edge(&G, 2, 4);
    add_edge(&G, 4, 5);
    int i;
    for (i=1; i<=G.n; i++){
        printf("degree(%d)= %d\n",i, degree(&G, i));
    }
    return 0;
}