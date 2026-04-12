#include <stdio.h>
#define size 100
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype other;
} record;

void ReadData(record a[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f == NULL){
		printf("Loi mo file!!!");
		return;
	}
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%d%f", &a[i].key, &a[i].other);
		i++;
	}
	*n = i;
	fclose(f);
}

void PrintData(record a[], int n){
	for(int i = 0; i < n; i++)
		printf("%3d %3d %8.2f\n", i+1,a[i].key, a[i].other);
}

void swap(record *a, record *b){
	record tmp = *a;
	*a = *b;
	*b = tmp;
}
//BubbleSort
void BubbleSort(record a[], int n){
	for(int i = 0; i < n-1; i++)
		for(int j = n-1; j >= 1; j--)
			if(a[j-1].key > a[j].key)
				swap(&a[j-1], &a[j]);
}

//SelectionSort
void SelectionSort(record a[], int n){
	for(int i = 0; i < n-1; i++){
		int lowidx = i; keytype tmp = a[lowidx].key;
		for(int j = i+1; j < n; j++)
			if(tmp > a[j].key){
				lowidx = j;
				tmp = a[lowidx].key;
			}
		swap(&a[i], &a[lowidx]);
	}
}

//InsertionSort
void InsertionSort(record a[], int n){
	for(int i = 0; i < n; i++){
		int j = i;
		while (j > 0 && a[j-1].key > a[j].key){
			swap(&a[j-1], &a[j]);
			j--;
		}
	}
}

//Quicksort
//Tim chot
int findPivot(record a[], int i, int j){
	keytype firstkey = a[i].key;
	for(int k = i+1; k <= j; k++){
		if(a[k].key != firstkey){
			return (a[k].key > firstkey)?k:i;
		}
	}
	return -1;
}

//Phan Hoach
int partition(record a[], int L, int R, keytype pivot){
	while(L <= R){
		while (a[L].key < pivot) L++;
		while (a[R].key >= pivot) R--;
		if(L < R) swap(&a[L], &a[R]);
	}
	return L;
}
//QuickSort

void QuickSort(record a[], int L, int R){
	int pivotidx = findPivot(a,L,R);
	if(pivotidx != -1){
		int k = partition(a, L, R, a[pivotidx].key);
		QuickSort(a, L, k-1);
		QuickSort(a, k, R);
	}
}

//Heapsort
void PushDown(record a[], int first, int last){
	int f = first;
	while (f <= (last-1)/2){
		int L = 2*f + 1, R = 2*f + 2;
		if(L == last){
			if(a[f].key > a[L].key)
				swap(&a[f], &a[L]);
			return;
		}
		if((a[f].key > a[L].key) && (a[L].key <= a[R].key)){
			swap(&a[f], &a[L]);
			f = L;
		}
		else if((a[f].key > a[R].key) && (a[L].key > a[R].key)){
			swap(&a[f], &a[R]);
			f = R;
		}
		else return;
	}
}

void HeapSort(record a[], int n){
	for(int i = (n-2)/2; i >= 0; i--)
		PushDown(a,i,n-1);/**/
	for(int i = n-1; i >= 2; i--){
		swap(&a[0],&a[i]);
		PushDown(a, 0, i-1);
	}
	swap(&a[0], &a[1]);
}
int main(){
	record a[size]; int n;
	ReadData(a,&n);
	printf("\nDu lieu truoc khi sap xep:\n");
	PrintData(a, n);
	printf("\nDu lieu sau khi sap xep:\n");
//	BubbleSort(a,n);
//	SelectionSort(a,n);
//	InsertionSort(a,n);
//	QuickSort(a, 0, n-1);
	HeapSort(a,n);
	PrintData(a, n);
	return 0;
}
