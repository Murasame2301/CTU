#include <stdio.h>
#define oo 100000

typedef struct {
    int A[100][100];
    int n, m;
} Graph;

void init_Graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pG->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v, int w) {
    pG->A[u][v] = w;
    pG->A[v][u] = w;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v){
    return pG->A[u][v] == 1;
}
int parent[100];
int pi[100];
int mark[100];

int Prim(Graph *pG, int s ,Graph *pT){
  int n = pG->n;
  for (int i = 1; i <= n; i++){
    pi[i] = oo;
    parent[i] = -1;
    mark[i] = 0;
  }
  pi[s] = 0;
  for (int it = 1; it <= n; it ++){
    int u  = -1;
    int val = oo;
    for (int i = 1; i <= n ; i++){
      if (!mark[i] && pi[i] < val){
        val = pi[i];
        u = i;
      }
    }
    mark[u] = 1;
    for (int v = 1; v <= n; v++){
      if (pG->A[u][v] && !mark[v] && pi[v] > pG->A[u][v]){
        pi[v] = pG->A[u][v];
        parent[v] = u;
      }
    }
  }
  init_Graph(pT, n);
  int sum = 0 ;
  for (int u = 1; u <= n ; u++){
    if (parent[u] != -1){
      sum+= pG->A[parent[u]][u];
      add_edge(pT, parent[u], u, pG->A[parent[u]][u]);
    }
  }
  return sum;
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  Graph G; init_Graph(&G, n);
  for (int i = 1; i <= m; i++) {
    int x, y,w;
    scanf("%d%d%d", &x, &y, &w);
    add_edge(&G, x, y,w);
  }
  Graph T;
  int sum = Prim(&G, 1, &T);
  printf("%d\n", sum);
  for (int u = 1; u <= n; u++){
    for (int v =1 ;v <= n ;v ++){
      if (T.A[u][v] && u < v){
        printf("%d %d %d\n",u , v, T.A[u][v]);
      }
    }
  }
  return 0;
}
