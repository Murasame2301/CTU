#include <stdio.h>
#define size 50

typedef int keytype;
typedef float othertype;

typedef struct{
	keytype key;
	othertype other;
} record;

void swap(record *a, record *b){
	record tmp = *a;
	*a = *b;
	*b = tmp;
}

int findPivot(record a[], int i, int j){
	keytype firstkey = a[i].key;
	for(int k = i+1; k <= j; k++){
		if(a[k].key != firstkey)
			return (a[k].key > firstkey)?k:i;
	}
	return -1;
}

int partition(record a[], int L, int R, keytype pivot){
	while (L <= R){
		while (a[L].key < pivot) L++;
		while (a[R].key >= pivot) R--;
		if(L < R) swap(&a[L], &a[R]);
	}
	return L;
}

void quickSort(record a[], int L, int R){
	int pivotidx = findPivot(a,L,R);
	if(pivotidx != -1){
		int k = partition(a,L,R,a[pivotidx].key);
		quickSort(a,L,k-1);
		quickSort(a,k,R);
	}
}

void readFile(record a[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%d%f", &a[*n].key, &a[*n].other);
			(*n)++;
		}
	}
	else printf("loi moi file\n");
	fclose(f);
}


void printData(record a[], int n, int m){
	if(n < m)
		for(int i = n; i < m; i++)
			printf("%3d %5d %8.2f\n", i+1, a[i].key, a[i].other);
	else
		for(int i = n-1; i >= m; i--){
			printf("%3d %5d %8.2f\n", n-i, a[i].key, a[i].other);
		}
}

int main() {
	record a[size];
	int n = 0;
	printf("Thuat toan Quick Sort\n");
	readFile(a, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(a, 0, n);
	quickSort(a,0,n-1);
	printf("Du lieu sau khi sap xep:\n");
	printData(a, 0, n);
	return 0;
}
