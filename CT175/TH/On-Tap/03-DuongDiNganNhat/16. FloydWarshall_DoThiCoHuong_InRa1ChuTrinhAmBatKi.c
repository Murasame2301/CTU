#include <stdio.h>
#define MAX_N 500
#define oo 10000000

typedef struct{
    int W[MAX_N][MAX_N];
    int n,m;
} Graph;

void init_graph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j) pG->W[i][j] = 0;
            else pG->W[i][j] = oo;
        }
    }
}

void add_edge(Graph *pG, int u, int v, int w){
    if(w < pG->W[u][v]) pG->W[u][v] = w;
}

int pi[MAX_N][MAX_N], next[MAX_N][MAX_N], negative_cycle;

void FloydWarshall(Graph *pG){
    int u, v, k;
    for(u = 1; u <= pG->n; u++){
        for(v = 1; v <= pG->n; v++){
            pi[u][v] = pG->W[u][v];
            if(pG->W[u][v] != oo && u != v) next[u][v] = v;
            else next[u][v] = -1;
        }
        next[u][u] = u;
    }
    for(k = 1; k <= pG->n; k++){
        for(u = 1; u <= pG->n; u++){
            if(pi[u][k] == oo) continue;
            for(v = 1; v <= pG->n; v++){
                if(pi[k][v] == oo) continue;
                if(pi[u][k] + pi[k][v] < pi[u][v]){
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
            }
        }
    }
//Kiem tra chu trinh am
    for(u = 1; u <= pG->n; u++){
        if(pi[u][u] < 0){
            negative_cycle = 1;
            break;
        }
    }
}

int len, cycle[MAX_N];

int build_negative_cycle(Graph *pG){
    int s = -1;
    for(int i = 1; i <= pG->n; i++){
        if(pi[i][i] < 0){
            s = i;
            break;
        }
    }
    if(s == -1) return 0;
    
    //Tim 1 dinh chac chan nam trong chu trinh bang cach "di n buoc"
    int x = s;
    for(int t = 1; t <= pG->n; t++){
        if(next[x][s] == -1) return 0;//Khong co duong quay ve s
        x = next[x][s];//Di theo duong x -> s
    }

	//Dung lai chu trinh bat dau tu x: Di den khi nao lap lai x
	//cur la dinh lap lai
	//start se la vi tri bat dau chu trinh that su
    len = 0;
    int cur = x;
	//Danh dau de tranh lap vo han
    int seen[MAX_N];
    for(int i = 1; i <= pG->n; i++) seen[i] = 0;

    while(!seen[cur]){
        if(cur == -1) return 0;
        seen[cur] = 1;
        cycle[len++] = cur;
        if(len > pG->n + 5) return 0;
        cur = next[cur][s];
        if(cur == -1) return 0;
    }

    
    int start = 0;
    while(start < len && cycle[start] != cur) start++;

    
    int newLen = 0;
    for(int i = start; i < len; i++) cycle[newLen++] = cycle[i];
    len = newLen;

    return (len > 0);
}

int main(){
    int n,m;
    Graph G;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    FloydWarshall(&G);
    if(build_negative_cycle(&G)){
        printf("YES\n");
        for(int i = 0; i < len; i++){
            printf("%d -> ", cycle[i]);
        }
        printf("%d",cycle[0]);
    }
	else{
        printf("NO");
    }
    return 0;
}
