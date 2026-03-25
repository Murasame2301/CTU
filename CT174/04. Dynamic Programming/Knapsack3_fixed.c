#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 1000
#define MAX_NAME 100

typedef struct {
    int w;
    int v;
    int qty;
    char name[MAX_NAME];
} Item;

void readFile(Item a[], int *n, int *m) {
    FILE *f = fopen("QHD_CaiBalo.inp", "r");
    if (f == NULL) {
        printf("Khong mo duoc file QHD_CaiBalo.inp\n");
        *n = 0;
        *m = 0;
        return;
    }

    fscanf(f, "%d", m);
    *n = 0;

    while (*n < MAX_N && fscanf(f, "%d %d %[^\n]", &a[*n].w, &a[*n].v, a[*n].name) == 3) {
        size_t len = strlen(a[*n].name);
        while (len > 0 && (a[*n].name[len - 1] == '\r' || a[*n].name[len - 1] == ' ' || a[*n].name[len - 1] == '\t')) {
            a[*n].name[len - 1] = '\0';
            len--;
        }
        a[*n].qty = 0;
        (*n)++;
    }

    fclose(f);
}

void printInput(Item a[], int n, int m) {
    printf("Du lieu bai toan Cai ba lo 3 (moi do vat chi co 1 cai):\n");
    printf("Trong luong ba lo m = %d\n", m);
    printf("|----|-----------------------|-------------|---------|\n");
    printf("|%-4s|%-23s|%-13s|%-9s|\n", "STT", "Ten do vat", "Trong luong", "Gia tri");
    printf("|----|-----------------------|-------------|---------|\n");
    for (int i = 0; i < n; i++) {
        printf("|%4d|%-23s|%13d|%9d|\n", i + 1, a[i].name, a[i].w, a[i].v);
    }
    printf("|----|-----------------------|-------------|---------|\n\n");
}

void createTable(Item a[], int n, int m, int F[][MAX_M + 1], int X[][MAX_M + 1]) {
    for (int j = 0; j <= m; j++) {
        if (j >= a[0].w) {
            F[0][j] = a[0].v;
            X[0][j] = 1;
        } else {
            F[0][j] = 0;
            X[0][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            F[i][j] = F[i - 1][j];
            X[i][j] = 0;

            if (j >= a[i].w) {
                int candidate = F[i - 1][j - a[i].w] + a[i].v;
                if (candidate > F[i][j]) {
                    F[i][j] = candidate;
                    X[i][j] = 1;
                }
            }
        }
    }
}

void printTable(int n, int m, int F[][MAX_M + 1], int X[][MAX_M + 1]) {
    printf("Bang quy hoach dong [F, X]:\n");
    printf("Moi o co dang (F, X), trong do F la gia tri toi uu va X cho biet co chon vat dang xet hay khong.\n\n");

    printf("|Vat\\TL ");
    for (int j = 0; j <= m; j++) {
        printf("| %5d ", j);
    }
    printf("|\n");

    for (int i = 0; i < n; i++) {
        printf("|x%-6d", i + 1);
        for (int j = 0; j <= m; j++) {
            printf("|(%2d,%2d)", F[i][j], X[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void traceResult(Item a[], int n, int m, int X[][MAX_M + 1]) {
    int remain = m;
    for (int i = n - 1; i >= 0; i--) {
        a[i].qty = X[i][remain];
        remain -= a[i].qty * a[i].w;
    }
}

void printResult(Item a[], int n, int m, int F[][MAX_M + 1]) {
    int totalWeight = 0;
    int totalValue = 0;

    printf("Phuong an toi uu duoi dang danh sach X(x1, ..., xn):\n");
    printf("X(");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i].qty);
        if (i < n - 1) printf(", ");
        totalWeight += a[i].qty * a[i].w;
        totalValue += a[i].qty * a[i].v;
    }
    printf(")\n\n");

    printf("|----|-----------------------|-------------|---------|-------------|\n");
    printf("|%-4s|%-23s|%-13s|%-9s|%-13s|\n", "STT", "Ten do vat", "Trong luong", "Gia tri", "Phuong an");
    printf("|----|-----------------------|-------------|---------|-------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|%4d|%-23s|%13d|%9d|%13d|\n", i + 1, a[i].name, a[i].w, a[i].v, a[i].qty);
    }
    printf("|----|-----------------------|-------------|---------|-------------|\n");

    printf("Trong luong cua ba lo        = %d\n", m);
    printf("Tong trong luong do vat chon = %d\n", totalWeight);
    printf("Tong gia tri lon nhat        = %d\n", totalValue);
    printf("Gia tri toi uu F[n-1][m]     = %d\n", F[n - 1][m]);
}

int main() {
    Item a[MAX_N];
    int n, m;
    static int F[MAX_N][MAX_M + 1];
    static int X[MAX_N][MAX_M + 1];

    readFile(a, &n, &m);
    if (n == 0) return 1;

    printInput(a, n, m);
    createTable(a, n, m, F, X);
    printTable(n, m, F, X);
    traceResult(a, n, m, X);
    printResult(a, n, m, F);

    return 0;
}
