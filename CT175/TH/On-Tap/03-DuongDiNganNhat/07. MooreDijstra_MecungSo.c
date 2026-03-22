#include <stdio.h>

int di[] = {-1, 1, 0 ,0};
int dj[] = {0 ,0, -1, 1};
int pi[100][100];
int mark[100][100];
void MooreDijkstra(int a[][100], int n ,int m){
    for (int i = 1 ; i <= n; i++){
        for (int j = 1; j <= m; j++){
            mark[i][j] = 0;
            pi[i][j] = 99999;
        }
    }
    pi[1][1] = 0;
    for (int it = 0; it < n*m; it ++){
        int tmp = 99999; 
        int u,v;
        for (int i = 1 ; i <= n; i++){
            for (int j = 1; j <= m ; j++){
                if (!mark[i][j] && pi[i][j] < tmp){
                    tmp = pi[i][j];
                    u = i; v = j;
                }
            }
        }
        mark[u][v] = 1;
        for (int i = 0; i < 4 ; i++){
            int new_u = u + di[i];
            int new_v = v + dj[i];
            if (new_u > 0 && new_u <= n && new_v >0 && new_v <= m && !mark[new_u][new_v]){
                if (pi[new_u][new_v] > pi[u][v] + a[new_u][new_v]){
                    pi[new_u][new_v] = pi[u][v] + a[new_u][new_v];
                }
            }
        }

    }
}
int main(){
    int n,m; 
    scanf("%d%d", &n, &m);
    int a[100][100];
    for (int i = 1; i <= n ; i++){
        for (int j = 1; j <=m ; j++){
            scanf("%d", &a[i][j]);
        }
    }
    MooreDijkstra(a, n ,m);
    printf("%d", pi[n][m]);

    return 0;
}
