#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[30];
    int wei,val,num,PA;
    float unit_price;
}Object;

Object* readData(int *W,int *n){
    Object *pO;
    int i=0;
    FILE *f;
    
    f=fopen("bag2.txt","r");

    fscanf(f,"%d",W);

    pO=(Object*)malloc(sizeof(Object));
    while(!feof(f)){
        fscanf(f,"%d%d%d%[^\n]",&pO[i].wei,&pO[i].val,&pO[i].num,&pO[i].name);
        float tmp;
        tmp=(float)pO[i].val/pO[i].wei;
        pO[i].unit_price=tmp;
        pO[i].PA=0;
        i++;
        pO=realloc(pO,(i+1)*sizeof(Object));
    }
    *n=i;
    return pO;
}

void swap(Object *a, Object *b){
    Object tmp=*a;
    *a=*b;
    *b=tmp;
}

void bubbleSort(Object t[],int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=n-1;j>=i+1;j--){
            if(t[j-1].unit_price<t[j].unit_price){
                swap(&t[j-1],&t[j]);
            }
        }
    }
}

void greddy(Object t[], int n, int W, int *W_conlai){
    int i=0;
    while(W>0 && i<n){
        int num=W/t[i].wei;
        if(num>t[i].num) num=t[i].num;
        t[i].PA=num;
        W=W-(t[i].PA*t[i].wei);
        i++;
    }
    *W_conlai=W;
}

void inDS(Object t[],int n, int w, int w_conlai){
    int i,j;
    printf("bai toan cai ba lo 2:\n");
    printf("|-----|------|------|------|------|--------------------|------|\n");
    printf("|-STT-|--TL--|--GT--|--DG--|--SL--|-----Ten do vat-----|--PA--|\n");
    for(i=0;i<n;i++){
        printf("|%-5d|%-6d|%-6d|%-6.2f|%-6d|%-20s|%6d|\n",i+1,t[i].wei,t[i].val,t[i].unit_price,t[i].num,t[i].name,t[i].PA);
    }
    printf("|-----|------|------|------|------|--------------------|------|\n");
    printf("Phuong an (tu cao den thap): (");
        for(i=0;i<n;i++){
            printf("%d",t[i].PA);
            if(i!=n-1){
                printf(",");
            }
        }
        printf(")\n");
    printf("Tong trong luong: %d\n",w-w_conlai);

    int tonggt=0;
    for(i=0;i<n;i++){
        if(t[i].PA){
            tonggt+=t[i].PA*t[i].val;
        }
    }
    printf("Tong gia tri: %d",tonggt);
}

int main(){
    Object *pO;
    int W,n,W_conlai; 

    pO=readData(&W,&n);
    bubbleSort(pO,n);
     
    greddy(pO,n,W,&W_conlai);
    inDS(pO,n,W,W_conlai);
    return 0;
}