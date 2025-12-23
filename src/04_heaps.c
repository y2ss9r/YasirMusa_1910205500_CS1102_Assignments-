#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *a;
    int size, cap;
    int is_min; // 1=min-heap, 0=max-heap
} Heap;

int cmp(Heap *h, int x, int y) {
    return h->is_min ? (x < y) : (x > y);
}

Heap *heap_create(int cap, int is_min) {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->a = (int*)malloc(sizeof(int) * cap);
    h->size = 0; h->cap = cap; h->is_min = is_min;
    return h;
}

void heap_swap(int *x, int *y) { int t=*x; *x=*y; *y=t; }

void heapify_up(Heap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (cmp(h, h->a[i], h->a[p])) {
            heap_swap(&h->a[i], &h->a[p]);
            i = p;
        } else break;
    }
}

void heapify_down(Heap *h, int i) {
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, best = i;
        if (l < h->size && cmp(h, h->a[l], h->a[best])) best = l;
        if (r < h->size && cmp(h, h->a[r], h->a[best])) best = r;
        if (best != i) { heap_swap(&h->a[i], &h->a[best]); i = best; }
        else break;
    }
}

int heap_insert(Heap *h, int val) {
    if (h->size == h->cap) return 0;
    h->a[h->size] = val;
    heapify_up(h, h->size);
    h->size++;
    return 1;
}

int heap_extract_root(Heap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->a[0];
    h->a[0] = h->a[h->size - 1];
    h->size--;
    heapify_down(h, 0);
    return 1;
}

void heap_print(Heap *h) {
    for (int i = 0; i < h->size; i++) printf("%d ", h->a[i]);
    printf("\n");
}

void heap_free(Heap *h) { free(h->a); free(h); }

int main(void) {
    int vals[] = {10, 4, 7, 1, 9, 3, 20};
    int n = (int)(sizeof(vals)/sizeof(vals[0]));

    Heap *minh = heap_create(64, 1);
    Heap *maxh = heap_create(64, 0);

    for (int i = 0; i < n; i++) {
        heap_insert(minh, vals[i]);
        heap_insert(maxh, vals[i]);
    }

    printf("Min-Heap array: "); heap_print(minh);
    printf("Max-Heap array: "); heap_print(maxh);

    int x;
    heap_extract_root(minh, &x);
    printf("Extract min = %d, after: ", x); heap_print(minh);

    heap_extract_root(maxh, &x);
    printf("Extract max = %d, after: ", x); heap_print(maxh);

    heap_free(minh);
    heap_free(maxh);
    return 0;
}