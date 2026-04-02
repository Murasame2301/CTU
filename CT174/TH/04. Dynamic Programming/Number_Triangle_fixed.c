#include <stdio.h>

#define MAX_N 50
#define NEG_INF -1000000000

void readFile(int a[][MAX_N], int *n) {
    FILE *f = fopen("tam_giac_so.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc file tam_giac_so.txt\n");
        *n = 0;
        return;
    }

    int i = 0;
    while (1) {
        int ok = 1;
        for (int j = 0; j <= i; j++) {
            if (fscanf(f, "%d", &a[i][j]) != 1) {
                ok = 0;
                break;
            }
        }
        if (!ok) break;
        i++;
    }

    *n = i;
    fclose(f);
}

void printTriangle(int a[][MAX_N], int n) {
    printf("Tam giac so da cho:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }
}

void createTable(int a[][MAX_N], int n, int F[][MAX_N], int trace[][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_N; j++) {
            F[i][j] = NEG_INF;
            trace[i][j] = -1;
        }
    }

    F[0][0] = a[0][0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                F[i][j] = F[i - 1][j] + a[i][j];
                trace[i][j] = j;
            } else if (j == i) {
                F[i][j] = F[i - 1][j - 1] + a[i][j];
                trace[i][j] = j - 1;
            } else {
                if (F[i - 1][j - 1] > F[i - 1][j]) {
                    F[i][j] = F[i - 1][j - 1] + a[i][j];
                    trace[i][j] = j - 1;
                } else {
                    F[i][j] = F[i - 1][j] + a[i][j];
                    trace[i][j] = j;
                }
            }
        }
    }
}

void printTable(int F[][MAX_N], int n) {
    printf("Bang quy hoach dong F:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%5d", F[i][j]);
        }
        printf("\n");
    }
}

int searchPath(int a[][MAX_N], int n, int F[][MAX_N], int trace[][MAX_N], int path[]) {
    int maxSum = F[n - 1][0];
    int col = 0;

    for (int j = 1; j < n; j++) {
        if (F[n - 1][j] > maxSum) {
            maxSum = F[n - 1][j];
            col = j;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        path[i] = a[i][col];
        col = trace[i][col];
    }

    return maxSum;
}

void printPath(int path[], int n, int sum) {
    printf("Phuong an (duong di toi uu):\n");
    for (int i = 0; i < n; i++) {
        printf("%d", path[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\nTong gia tri lon nhat: %d\n", sum);
}

int main() {
    int a[MAX_N][MAX_N];
    int F[MAX_N][MAX_N];
    int trace[MAX_N][MAX_N];
    int path[MAX_N];
    int n = 0;

    readFile(a, &n);
    if (n == 0) return 1;

    printTriangle(a, n);
    createTable(a, n, F, trace);
    printTable(F, n);
    int sum = searchPath(a, n, F, trace, path);
    printPath(path, n, sum);

    return 0;
}
