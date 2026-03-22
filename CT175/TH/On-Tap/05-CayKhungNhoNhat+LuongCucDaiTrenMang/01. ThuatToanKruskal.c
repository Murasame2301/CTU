#include <stdio.h>

typedef struct {
   int x,y,w;
}Edge;

typedef struct {
  Edge edges[100];
  int n, m;
}Graph;

void init_Graph(Graph *pG, int n){
  pG->n = n;
  pG->m = 0;
}
void add_edge(Graph *pG, int u, int v, int z){
  pG->edges[pG->m].x = u;
  pG->edges[pG->m].y = v;
  pG->edges[pG->m].w = z;
  pG->m++;
}


int parent[100];
int find_root(int u){
  while (parent[u] != u){
    u = parent[u];
  }
  return u;
}

void bubble_sort(Graph *pG){
  for (int i = 0 ; i < pG->m-1; i++){
    for (int j =pG->m-1; j > 0;j--){
      if (pG->edges[j].w < pG->edges[j-1].w){
        Edge tmp = pG->edges[j] ;
        pG->edges[j] = pG->edges[j-1];
        pG->edges[j-1]= tmp;
      }
    }
  }
}

int krusal(Graph *pG ,Graph *T){
  init_Graph(T, pG->n);
  bubble_sort(pG);
  int n = pG->n;
  int m = pG->m;
  for (int i = 1; i <= n ; i++){
    parent[i] = i;
  }
  int sum = 0;
  for (int i = 0; i < m; i++){
    int u = pG->edges[i].x;
    int v = pG->edges[i].y;
    int w = pG->edges[i].w;
    int root_u = find_root(u);
    int root_v = find_root(v);
    if (root_u != root_v){
      if (u < v ) add_edge(T, u, v, w);
      else add_edge(T, v, u, w);
      parent[root_v] = root_u;
      sum += w;
    }
  }
  return sum;
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  Graph G; init_Graph(&G, n);
  for (int i = 1; i <= m; i++) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    add_edge(&G, x, y,w);
  }
  Graph T; 
  int total = krusal(&G, &T);
  printf("%d\n", total);
  for (int  i =0 ; i < T.m; i++){
    printf("%d %d %d\n", T.edges[i].x, T.edges[i].y, T.edges[i].w);
  }
  return 0;
}
