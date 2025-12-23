#include <stdio.h>

#define MAXN 100

void dfs(int n, int g[MAXN][MAXN], int u, int visited[MAXN]) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < n; v++) {
        if (g[u][v] && !visited[v]) dfs(n, g, v, visited);
    }
}

void bfs(int n, int g[MAXN][MAXN], int start) {
    int visited[MAXN] = {0};
    int q[MAXN], front = 0, back = 0;

    visited[start] = 1;
    q[back++] = start;

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
}

int main(void) {
    int n, start;
    int g[MAXN][MAXN];

    printf("n: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAXN) return 0;

    printf("Adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    printf("Start node: ");
    scanf("%d", &start);
    if (start < 0 || start >= n) return 0;

    int visited[MAXN] = {0};
    printf("DFS: ");
    dfs(n, g, start, visited);
    printf("\n");

    printf("BFS: ");
    bfs(n, g, start);
    printf("\n");
    return 0;
}