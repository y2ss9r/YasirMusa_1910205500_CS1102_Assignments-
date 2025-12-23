#include <stdio.h>

#define MAXN 100

void bfs_component(int n, int g[MAXN][MAXN], int start, int visited[MAXN]) {
    int q[MAXN], front = 0, back = 0;
    q[back++] = start;
    visited[start] = 1;

    printf("{ ");
    while (front < back) {
        int u = q[front++];
        printf("%d ", u);

        for (int v = 0; v < n; v++) {
            if (g[u][v] && !visited[v]) {
                visited[v] = 1;
                q[back++] = v;
            }
        }
    }
    printf("}\n");
}

int main(void) {
    int n;
    int g[MAXN][MAXN];
    int visited[MAXN] = {0};

    printf("Enter number of nodes (<=100): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAXN) return 0;

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    int comp = 0;
    printf("Connected Components (Clusters):\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Component %d: ", ++comp);
            bfs_component(n, g, i, visited);
        }
    }
    return 0;
}