#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 1024

typedef struct {
    char st[MAX];
    int top;
} CharStack;

void push(CharStack *s, char c) { s->st[++s->top] = c; }
char pop(CharStack *s) { return s->st[s->top--]; }
char peek(CharStack *s) { return s->st[s->top]; }
int empty(CharStack *s) { return s->top == -1; }

int prec(char op) {
    switch (op) {
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}
int right_assoc(char op) { return op == '^'; }

int is_op(char c) { return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'; }

void infix_to_postfix(const char *infix, char *out) {
    CharStack s; s.top = -1;
    int j = 0;

    for (int i = 0; infix[i]; ) {
        if (isspace((unsigned char)infix[i])) { i++; continue; }

        if (isdigit((unsigned char)infix[i])) {
            while (isdigit((unsigned char)infix[i])) out[j++] = infix[i++];
            out[j++] = ' ';
            continue;
        }

        if (infix[i] == '(') { push(&s, '('); i++; continue; }

        if (infix[i] == ')') {
            while (!empty(&s) && peek(&s) != '(') { out[j++] = pop(&s); out[j++] = ' '; }
            if (!empty(&s) && peek(&s) == '(') pop(&s);
            i++;
            continue;
        }

        if (is_op(infix[i])) {
            char op = infix[i];
            while (!empty(&s) && is_op(peek(&s))) {
                char top = peek(&s);
                if (prec(top) > prec(op) || (prec(top) == prec(op) && !right_assoc(op))) {
                    out[j++] = pop(&s); out[j++] = ' ';
                } else break;
            }
            push(&s, op);
            i++;
            continue;
        }

        // variables (optional): a, b, x...
        if (isalpha((unsigned char)infix[i])) {
            out[j++] = infix[i++];
            out[j++] = ' ';
            continue;
        }

        // unknown char
        i++;
    }

    while (!empty(&s)) {
        char c = pop(&s);
        if (c != '(') { out[j++] = c; out[j++] = ' '; }
    }
    out[j] = '\0';
}

int main(void) {
    char infix[MAX], postfix[MAX];
    printf("Enter infix: ");
    fgets(infix, sizeof(infix), stdin);

    infix_to_postfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    return 0;
}