#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float dodai;
    int dau,cuoi;
}canh;

canh* readData(int *n){
    canh* tmp;
    int i,j,z,k;
    FILE *f;
    float x;
    k=0;

    f=fopen("TSP.txt","r");
    tmp = (canh*)malloc(sizeof(canh));
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++){
        for(j=i;j<*n;j++){
            if(i==j) for(z=0;z<=j;z++) fscanf(f,"%f",&x);
            else{
                fscanf(f,"%f",&tmp[k].dodai);
                tmp[k].dau=i;
                tmp[k].cuoi=j;
                k++;
                tmp=(canh*)realloc(tmp,(k+1)*sizeof(canh));
            }
        }
    }
    return tmp;
}

void inds(canh a[],int m,int laPA){
    int i;
    float tong=0;
    for(i=0;i<m;i++){
        printf("%2d.%c%c=%4.2f\n",i+1,a[i].dau+97,a[i].cuoi+97,a[i].dodai);
        if(laPA){
            tong+=a[i].dodai;
        }   
    }
    if(laPA){
        printf("Tong do dai cai canh cua phuong an: %5.2f",tong);
    }
}

void swap(canh *a, canh *b){
    canh tmp=*a;
    *a=*b;
    *b=tmp;
}

void bubbleSort(canh a[],int n){
    int i,j;
    n=n*(n-1)/2;
    for(i=1;i<=n-1;i++){
        for(j=n-1;j>=i;j--){
            if(a[j-1].dodai>a[j].dodai){
                swap(&a[j-1],&a[j]);
            }
        }
    }
}

int dinhcap3(canh PA[],int k,canh moi){
    int i;
    int dem;
    i=0;    dem=1;
    while(i<k && dem!=3){
        if(PA[i].dau==moi.dau || PA[i].cuoi==moi.dau) dem++;
        i++;
    }
    if(dem==3) return 1;

    i=0;    dem=1;
    while(i<k && dem!=3){
        if(PA[i].dau==moi.cuoi || PA[i].cuoi==moi.cuoi) dem++;
        i++;
    }
    return dem==3;
}

void init_forest(int parent[],int n){
    int i;
    for(i=0;i<n;i++){
        parent[i]=i;
    }
}

int find_root(int parent[],int u){
    while(u!=parent[u]){
        u=parent[u];
    }
    return u;
}

int chutrinh(int dau, int cuoi){
    return dau==cuoi;
}

void update_forest(int parent[],int u, int v){
    parent[v]=u;
}

void greddy(canh a[], canh PA[], int n){
    int i,k,r_dau,r_cuoi;
    int parent[n];
    k=0;
    init_forest(parent,n);

    for(i=0;i<n*(n-1)/2 && k<n-1;i++){
        r_dau=find_root(parent,a[i].dau);
        r_cuoi=find_root(parent,a[i].cuoi);
        if(!dinhcap3(PA,k,a[i]) && !chutrinh(r_dau,r_cuoi)){
            PA[k]=a[i];
            update_forest(parent,r_dau,r_cuoi);
            k++;
        }
    }
    for(;i<n*(n-1)/2;i++){
        r_dau=find_root(parent,a[i].dau);
        r_cuoi=find_root(parent,a[i].cuoi);
        if(!dinhcap3(PA,k,a[i]) && chutrinh(r_dau,r_cuoi)){
            PA[k]=a[i];
            update_forest(parent,r_dau,r_cuoi);
            k++;
        }
    }
}

int main(){
    canh *dscanh;
    int n;

    dscanh = readData(&n);
    
    printf("danh sach canh ban dau:\n");
    inds(dscanh,n*(n-1)/2,0);

    bubbleSort(dscanh,n);
    printf("danh sach canh da sap xep:\n");
    inds(dscanh,n*(n-1)/2,0);

    canh PA[n];
    greddy(dscanh,PA,n);
    printf("danh sach ket qua:\n");
    inds(PA,n,1);

    return 0;
}