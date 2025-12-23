#include <stdio.h>

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1: %c -> %c\n", from, to);
        return;
    }
    hanoi(n - 1, from, aux, to);
    printf("Move disk %d: %c -> %c\n", n, from, to);
    hanoi(n - 1, aux, to, from);
}

int main(void) {
    int n;
    printf("Enter number of disks: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    hanoi(n, 'A', 'C', 'B');
    return 0;
}