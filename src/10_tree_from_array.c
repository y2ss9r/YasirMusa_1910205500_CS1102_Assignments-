#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* new_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = x; n->left = n->right = NULL;
    return n;
}

Node* build_tree(int arr[], int n, int i) {
    if (i >= n || arr[i] == -1) return NULL;
    Node* root = new_node(arr[i]);
    root->left = build_tree(arr, n, 2*i + 1);
    root->right = build_tree(arr, n, 2*i + 2);
    return root;
}

void preorder(Node* r) {
    if (!r) return;
    printf("%d ", r->data);
    preorder(r->left);
    preorder(r->right);
}
void inorder(Node* r) {
    if (!r) return;
    inorder(r->left);
    printf("%d ", r->data);
    inorder(r->right);
}
void postorder(Node* r) {
    if (!r) return;
    postorder(r->left);
    postorder(r->right);
    printf("%d ", r->data);
}

void free_tree(Node* r) {
    if (!r) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main(void) {
    // example: -1 means null
    int arr[] = {1, 2, 3, 4, -1, 6, 7};
    int n = (int)(sizeof(arr)/sizeof(arr[0]));

    Node* root = build_tree(arr, n, 0);

    printf("Preorder: "); preorder(root); printf("\n");
    printf("Inorder: "); inorder(root); printf("\n");
    printf("Postorder: "); postorder(root); printf("\n");

    free_tree(root);
    return 0;
}