#include <stdio.h>

int in[100];
int out[100];

int main(){
  int n, m; scanf("%d%d", &n,&m);
  int check = 1;
  for (int i =1; i <= m ; i++){
    int u, v ,c, f;
    scanf("%d%d%d%d", &u, &v, &c, &f);
    out[u] += f;
    in[v] += f;
    if (f > c) check = 0;
  }
  if (out[1] != in[n]) check = 0;
  for (int i = 2; i <= n-1 ; i++){
    if (in[i] !=out[i]) check = 0;
  }
  if (check == 0) printf("NO");
  else printf("YES");

  return 0;
}
