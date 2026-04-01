#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int TL,GT,PA,SL;
    char tendv[100];
}dovat;

dovat* readData(int *W, int *n){
    int i=0;
    dovat *tmp;
    FILE *f;

    f=fopen("bag2.txt","r");
    tmp=(dovat*)malloc(sizeof(dovat));
    fscanf(f,"%d",W);
    while(!feof(f)){
        fscanf(f,"%d%d%d%[^\n]",&tmp[i].TL,&tmp[i].GT,&tmp[i].SL,&tmp[i].tendv);
        tmp[i].PA=0;
        i++;
        tmp=(dovat*)realloc(tmp,(i+1)*sizeof(dovat));
    }
    *n=i;
    return tmp;
}



void createTable(dovat d[],int n,int W,int F[50][100], int X[50][100]){
    int k,V,xk,x;
    
    for(V=0;V<=W;V++){
        X[0][V]=V/d[0].TL;
        if(X[0][V]>d[0].SL) X[0][V]=d[0].SL;
        F[0][V]=X[0][V]*d[0].GT;
    }

    for(k=1;k<n;k++){
        for(V=0;V<=W;V++){
            xk=V/d[k].TL;
            if(xk>d[k].SL) xk=d[k].SL;

            X[k][V]=0;
            F[k][V]=F[k-1][V];
            for(x=1;x<=xk;x++){
                if(F[k-1][V-x*d[k].TL]+x*d[k].GT > F[k][V]){
                    X[k][V] = x;
                    F[k][V] = F[k-1][V-x*d[k].TL]+x*d[k].GT;
                }
            }
        }
    }
}

void searchTable(dovat d[],int n,int F[50][100], int X[50][100],int W){
    int k,V=W;
    for(k=n-1;k>=0;k--){
        d[k].PA = X[k][V];
        V = V - d[k].PA*d[k].TL;
    }
}

void printRes(dovat d[],int n){
    int i,GT_sum=0,TL_sum=0;
    printf("Bai toan cai balo giai bang ky thuat quy hoach dong:\n");
    printf("|---|--------------------|------|------|------|------|\n");
    printf("|STT|-----ten do vat-----|--TL--|--GT--|--SL--|--PA--|\n");
    for(i=0;i<n;i++){
        printf("|%-3d|%-20s|%-6d|%-6d|%-6d|%-6d|\n",i+1,d[i].tendv,d[i].TL,d[i].GT,d[i].SL,d[i].PA);
    }
    printf("|---|--------------------|------|------|------|------|\n");

    for(i=0;i<n;i++){
        GT_sum+=d[i].PA*d[i].GT;
        TL_sum+=d[i].PA*d[i].TL;
    }
    printf("Tong trong luong la: %d\n",TL_sum);
    printf("Tong gia tri la: %d\n",GT_sum);
}

void printTable(int n,int W,int F[50][100], int X[50][100]){
    int k,V;
    printf("   ");
    for(V=0;V<=W;V++) printf("|%-7d",V);
    printf("\n");
    for(k=0;k<n;k++){
        printf("%3d",k+1);
        for(V=0;V<=W;V++){
            printf("|%4d %2d",F[k][V],X[k][V]);
        }
        printf("\n");
    }
}

int main(){
    dovat *dsdv;
    int n,W;
    int F[50][100],X[50][100];

    dsdv = readData(&W,&n);
    createTable(dsdv,n,W,F,X);
    searchTable(dsdv,n,F,X,W);
    printTable(n,W,F,X);
    printRes(dsdv,n);
    return 0;
}
