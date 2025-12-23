#include <stdio.h>

int array_insert(int a[], int *n, int cap, int idx, int val) {
    if (*n >= cap || idx < 0 || idx > *n) return 0;
    for (int i = *n; i > idx; i--) a[i] = a[i-1];
    a[idx] = val;
    (*n)++;
    return 1;
}

int array_delete(int a[], int *n, int idx) {
    if (*n <= 0 || idx < 0 || idx >= *n) return 0;
    for (int i = idx; i < *n - 1; i++) a[i] = a[i+1];
    (*n)--;
    return 1;
}

void print_arr(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main(void) {
    int cap = 10, n = 5;
    int a[10] = {1,2,3,4,5};

    printf("Original: "); print_arr(a, n);

    array_insert(a, &n, cap, 2, 99);
    printf("After insert 99 at idx2: "); print_arr(a, n);

    array_delete(a, &n, 4);
    printf("After delete idx4: "); print_arr(a, n);

    return 0;
}