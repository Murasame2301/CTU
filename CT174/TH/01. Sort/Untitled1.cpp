#include <stdio.h>
#define size 50
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype other;
} record;
void ReadData(record a[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f==NULL){
		printf("Loi mo file!!!");
		return;
	}
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d", )
	}
}
int main(){
	return 0;
}
