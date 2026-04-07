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

void bubbleSort(record a[], int n){
	int i, j;
	for(i = 0; i < n-1; i++)
		for(j = n-1; j > i; j--)
			if(a[j-1].key > a[j].key)
				swap(&a[j-1],&a[j]);
}

void ReadData(record a[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f == NULL){
		printf("Loi mo file!!");
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
		printf("%3d %5d %8.2f\n", i+1,a[i].key, a[i].other);
}

int main() {
	int n;
	record a[size];
	ReadData(a,&n);
	printf("\nDu lieu truoc khi sap xep la:\n");
	PrintData(a,n);
	printf("\nDu lieu sau khi sap xep la:\n");
	bubbleSort(a,n);
	PrintData(a,n);
}
