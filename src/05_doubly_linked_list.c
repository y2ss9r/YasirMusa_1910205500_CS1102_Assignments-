#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* new_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = x; n->prev = n->next = NULL;
    return n;
}

void push_front(Node **head, int x) {
    Node *n = new_node(x);
    n->next = *head;
    if (*head) (*head)->prev = n;
    *head = n;
}

void insert_after(Node *pos, int x) {
    if (!pos) return;
    Node *n = new_node(x);
    n->next = pos->next;
    n->prev = pos;
    if (pos->next) pos->next->prev = n;
    pos->next = n;
}

void delete_value(Node **head, int x) {
    Node *cur = *head;
    while (cur && cur->data != x) cur = cur->next;
    if (!cur) return;

    if (cur->prev) cur->prev->next = cur->next;
    else *head = cur->next;

    if (cur->next) cur->next->prev = cur->prev;
    free(cur);
}

void traverse_forward(Node *head) {
    for (Node *p = head; p; p = p->next) printf("%d ", p->data);
    printf("\n");
}

void traverse_backward(Node *head) {
    if (!head) { printf("\n"); return; }
    Node *p = head;
    while (p->next) p = p->next;
    for (; p; p = p->prev) printf("%d ", p->data);
    printf("\n");
}

void free_list(Node *head) {
    while (head) { Node* t = head; head = head->next; free(t); }
}

int main(void) {
    Node *head = NULL;

    push_front(&head, 3);
    push_front(&head, 2);
    push_front(&head, 1); // 1 2 3

    printf("Forward: "); traverse_forward(head);
    printf("Backward: "); traverse_backward(head);

    insert_after(head->next, 99); // after 2 => 1 2 99 3
    printf("After insert: "); traverse_forward(head);

    delete_value(&head, 2);
    printf("After delete 2: "); traverse_forward(head);

    free_list(head);
    return 0;
}