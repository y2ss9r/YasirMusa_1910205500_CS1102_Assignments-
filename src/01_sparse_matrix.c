#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c, v;
} Triplet;

typedef struct {
    int rows, cols, nnz;
    Triplet *t;
} Sparse;

Sparse dense_to_sparse(int **a, int rows, int cols) {
    int nnz = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (a[i][j] != 0) nnz++;

    Sparse s;
    s.rows = rows; s.cols = cols; s.nnz = nnz;
    s.t = (Triplet*)malloc(sizeof(Triplet) * nnz);

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (a[i][j] != 0) {
                s.t[k].r = i;
                s.t[k].c = j;
                s.t[k].v = a[i][j];
                k++;
            }
        }
    }
    return s;
}

int **sparse_to_dense(Sparse s) {
    int **a = (int**)malloc(sizeof(int*) * s.rows);
    for (int i = 0; i < s.rows; i++) {
        a[i] = (int*)calloc(s.cols, sizeof(int));
    }

    for (int k = 0; k < s.nnz; k++) {
        a[s.t[k].r][s.t[k].c] = s.t[k].v;
    }
    return a;
}

void print_dense(int **a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void print_sparse(Sparse s) {
    printf("Sparse Triplets (row col val), nnz=%d:\n", s.nnz);
    for (int k = 0; k < s.nnz; k++)
        printf("%d %d %d\n", s.t[k].r, s.t[k].c, s.t[k].v);
}

int main(void) {
    int rows = 4, cols = 5;

    int **a = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) a[i] = (int*)calloc(cols, sizeof(int));

    a[0][1] = 3;  a[1][3] = 7;  a[3][0] = 9; a[2][4] = 5;

    printf("Dense Matrix:\n");
    print_dense(a, rows, cols);

    Sparse s = dense_to_sparse(a, rows, cols);
    print_sparse(s);

    int **b = sparse_to_dense(s);
    printf("\nBack to Dense:\n");
    print_dense(b, rows, cols);

    for (int i = 0; i < rows; i++) { free(a[i]); free(b[i]); }
    free(a); free(b);
    free(s.t);
    return 0;
}