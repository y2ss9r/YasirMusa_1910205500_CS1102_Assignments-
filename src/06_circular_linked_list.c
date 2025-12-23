#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* new_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = x; n->next = n;
    return n;
}

void insert_end(Node **head, int x) {
    Node *n = new_node(x);
    if (!*head) { *head = n; return; }
    Node *tail = *head;
    while (tail->next != *head) tail = tail->next;
    tail->next = n;
    n->next = *head;
}

void insert_after_value(Node *head, int key, int x) {
    if (!head) return;
    Node *p = head;
    do {
        if (p->data == key) {
            Node *n = new_node(x);
            n->next = p->next;
            p->next = n;
            return;
        }
        p = p->next;
    } while (p != head);
}

void delete_value(Node **head, int key) {
    if (!*head) return;

    Node *cur = *head, *prev = NULL;

    // search
    do {
        if (cur->data == key) break;
        prev = cur;
        cur = cur->next;
    } while (cur != *head);

    if (cur->data != key) return; // not found

    // single node
    if (cur->next == cur) {
        free(cur);
        *head = NULL;
        return;
    }

    // if deleting head, find tail
    if (cur == *head) {
        Node *tail = *head;
        while (tail->next != *head) tail = tail->next;
        *head = cur->next;
        tail->next = *head;
        free(cur);
        return;
    }

    // normal
    prev->next = cur->next;
    free(cur);
}

void traverse(Node *head) {
    if (!head) { printf("(empty)\n"); return; }
    Node *p = head;
    do {
        printf("%d ", p->data);
        p = p->next;
    } while (p != head);
    printf("\n");
}

void free_list(Node **head) {
    if (!*head) return;
    Node *p = (*head)->next;
    while (p != *head) {
        Node *t = p;
        p = p->next;
        free(t);
    }
    free(*head);
    *head = NULL;
}

int main(void) {
    Node *head = NULL;

    insert_end(&head, 1);
    insert_end(&head, 2);
    insert_end(&head, 3);

    printf("Traversal: "); traverse(head);

    insert_after_value(head, 2, 99);
    printf("After insert after 2: "); traverse(head);

    delete_value(&head, 1);
    printf("After delete 1: "); traverse(head);

    free_list(&head);
    return 0;
}