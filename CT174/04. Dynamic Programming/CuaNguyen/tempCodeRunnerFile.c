#include <stdio.h>

void readData(int arr[][100],int *n){
    FILE *f;
    f=fopen("matrix.txt","r");
    int i,j;

    while(!feof(f)){
        fscanf(f,"%d",&arr[i][j]);
        j++;
        if(j>i){
            j=0;
            i++;
        }
    }
    *n=i;
    fclose(f);
}

void printMatrix(int arr[][100],int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<=i;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

int maxInd(int F[][100],int n,int i,int j){
    if(j==0){
        if(F[i-1][j] >= F[i-1][j+1]) return j;
        else return j+1;
    }
    if(j==i){
        return j-1;
    }
    if(j==i-1){
        if(F[i-1][j-1] >= F[i-1][j]) return j-1;
        else return j;
    }
    else{
        int max=F[i-1][j-1];
        int tmp,maxind=j-1;
        for(tmp=0;tmp<=1;tmp++){
            if(F[i-1][j+tmp] > max){
                max=F[i-1][j+tmp];
                maxind=j+tmp;
            }
        }
        return maxind;
    }
}

void createTable(int arr[][100],int n, int F[][100],int C[][100]){
    int i,j,ind;
    for(i=0;i<n;i++){
        for(j=0;j<=i;j++){
            if(i==0){
                F[0][0]=arr[0][0];
                C[0][0]=0;
            }
            if(i==1){
                F[i][j]=F[0][0]+arr[i][j];
                C[i][j]=0;
            }
            if(i>1){
                ind=maxInd(F,n,i,j);
                F[i][j]=F[i-1][ind] + arr[i][j];
                C[i][j]=ind;
            }
        }
    }
}

void getPA(int arr[][100],int n, int F[][100],int C[][100],int PA[]){
    int max=F[n-1][0];
    int i,ind=0;

    for(i=1;i<n;i++){
        if(F[n-1][i]>max){
            max=F[n-1][i];
            ind=i;
        }
    }

    for(i=n-1;i>=0;i--){
        PA[i]=arr[i][ind];
        ind=C[i][ind];
    }
}

void printPA(int PA[],int n){
    int i,sum=0;
    printf("Duong di dai nhat: ");
    for(i=0;i<n;i++){
        printf("%d",PA[i]);
        sum+=PA[i];
        if(i!=n-1) printf("->");
    }
    printf("\nTong chi phi duong di dai nhat:%d",sum);
}

int main(){
    int arr[100][100];
    int n;
    
    readData(arr,&n);
    printf("ma tran de cho:\n");
    printMatrix(arr,n);
    int F[n][n],C[n][n],PA[n];

    createTable(arr,n,F,C);
    printf("ma tran sau khi su dung quy hoach dong :\n");
    printMatrix(F,n);
    getPA(arr,n,F,C,PA);
    printPA(PA,n);
    return 0;
}