#include <stdio.h>
#define MIN(a,b) (a>b)?(b):(a)
#define oo 100000
typedef int ElementType;

typedef struct{
  int C[100][100];
  int F[100][100];
  int n;
} Graph;

typedef struct{
  int dir;
  int p;
  int sigma;
}Label;

Label labels[100];
void init_flow(Graph *pG){
  for (int i = 1; i <= pG->n; i++){
    for (int j = 1; j <= pG->n; j++){
      pG->F[i][j] = 0;
    }
  }
}

typedef struct {
  ElementType data[100];
  int front, rear;
} Queue;

void makenull_Queue(Queue *pQ){ pQ->front = 0; pQ->rear = -1; }
void enqueue(Queue *pQ, ElementType u){ pQ->rear++; pQ->data[pQ->rear] = u; }
ElementType front(Queue *pQ){ return pQ->data[pQ->front]; }
void dequeue(Queue *pQ){ pQ->front++; }
int empty_Queue(Queue *pQ){ return pQ->front > pQ->rear; }


int FordFullkerson(Graph *pG ,int s, int t){
  int n = pG->n;
  init_flow(pG);
  int max_flow = 0;
  do {
    for (int i = 1; i <= n ; i++){
      labels[i].dir = 0;
    }
    labels[s].dir = 1;
    labels[s].p = -1;
    labels[s].sigma = oo;  
    Queue Q; makenull_Queue(&Q);
    enqueue(&Q, s);
    int found = 0;
    while (!empty_Queue(&Q)){
      int u = front(&Q); dequeue(&Q);
      for (int  v= 1; v <= n ; v++){
        if (pG->C[u][v] && labels[v].dir == 0 && pG->F[u][v] < pG->C[u][v]){
          labels[v].dir = 1;
          labels[v].p = u;
          labels[v].sigma = MIN(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);
          enqueue(&Q, v);
        }
      }
       if (labels[t].dir != 0){
        found = 1;
        break;
      }
      for (int  v= 1; v <= n ; v++){
        if (pG->C[v][u] && labels[v].dir == 0 && pG->F[u][v] > 0){
          labels[v].dir = -1;
          labels[v].p = u;
          labels[v].sigma = MIN(labels[u].sigma, pG->F[u][v]);
          enqueue(&Q, v);
        }
      }
      if (labels[t].dir != 0) {
        found = 1;
        break;
      }
    }
    if (found == 1){
      int sigma = labels[t].sigma;
      int u = t;
      while (u != s){
        int v = labels[u].p;
        if (labels[v].dir == 1){
          pG->F[v][u] += sigma;
        }
        else{
          pG->F[u][v] -= sigma;
        }
        u = v;
      }
      max_flow += sigma;
    }else break;
  }while (1);
  return max_flow;
}

int main(){
  Graph G; 
  int n, m; scanf("%d%d", &n, &m);
  G.n = n;
  for (int i = 1; i <= n ; i++){
    for (int j = 1; j <= n; j++){
      G.C[i][j] = 0;
    }
  }
  for (int i = 1 ; i <= m; i++){
    int u,v,w;
    scanf("%d%d%d", &u, &v ,&w);
    G.C[u][v] = w;
  }
  int max_flow = FordFullkerson(&G, 1, n);
  printf("Max flow: %d\n", max_flow);
  printf("S: ");
  for (int i = 1; i <=n ; i++){
    if (labels[i].dir != 0) printf("%d ", i);
  }
  printf("\nT: ");
  for (int i = 1; i <=n ; i++){
    if (labels[i].dir == 0) printf("%d ", i);
  }
  return 0;
}
