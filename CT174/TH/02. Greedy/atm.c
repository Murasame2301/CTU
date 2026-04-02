#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char loaitien[30];
    int sotien,PA;
}Tien;

Tien* readData(int *n){
    Tien *t;
    int i=0;
    FILE *f;

    f=fopen("atm.txt","r");
    t=(Tien*)malloc(sizeof(Tien));
    
    while(!feof(f)){
        fscanf(f,"%d %[^\n]",&t[i].sotien,&t[i].loaitien);
        t[i].PA=0;
        i++;
        t=(Tien*)realloc(t,(i+1)*sizeof(Tien));
    }

    *n=i;
    fclose(f);
    return t;
}

void swap(Tien *a, Tien *b){
    Tien tmp=*a;
    *a=*b;
    *b=tmp;
}

void bubbleSort(Tien t[],int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=n-1;j>=i+1;j--){
            if(t[j-1].sotien<t[j].sotien){
                swap(&t[j-1],&t[j]);
            }
        }
    }
}

void greddy(Tien t[], int n, int tienrut, int *tienthua){
    int i;
    for(i=0;i<n;i++){
        t[i].PA=tienrut/t[i].sotien;
        tienrut=tienrut-(t[i].PA*t[i].sotien);
    }
    *tienthua=tienrut;
}

void inDS(Tien t[],int n, int tienrut, int tienthua){
    int i;
    printf("bai toan ATM:\n");
    printf("|-----|----------|--------------------|-----|\n");
    for(i=0;i<n;i++){
        printf("|%-5d|%-10d|%-20s|%5d|\n",i+1,t[i].sotien,t[i].loaitien,t[i].PA);
    }
    printf("|-----|----------|--------------------|-----|\n");
    printf("tien can rut: %d\n",tienrut);
    printf("tien da rut: %d\n",tienrut-tienthua);
}

int main(){
    Tien *t;
    int n; 
    int tienrut,tienthua;

    t=readData(&n);
    printf("nhap so tien can rut: ");
    scanf("%d",&tienrut);
    bubbleSort(t,n);
    greddy(t,n,tienrut,&tienthua);
    inDS(t,n,tienrut,tienthua);
    return 0;
}