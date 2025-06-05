#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node {
    char data;
    struct node* next;
} node;

node* createnode(char data);
void pushChar(node** top, char data);
char popChar(node** top);
char peekChar(node* top);
int isEmptyChar(node* top);
int precedence(char op);
int isRightAssociative(char op);
int isOperator(char c);
void infixToPostfix(const char* infix, char* postfix);
void handleError(const char* message);

node* createnode(char data) {
    node* newnode = (node*)malloc(sizeof(node));
    if (!newnode) {
        handleError("Memory allocation failed");
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void pushChar(node** top, char data) {
    node* newnode = createnode(data);
    newnode->next = *top;
    *top = newnode;
}

char popChar(node** top) {
    if (isEmptyChar(*top)) {
        handleError("Stack underflow");
    }
    node* temp = *top;
    char poppedValue = temp->data;
    *top = temp->next;
    free(temp);
    return poppedValue;
}

char peekChar(node* top) {
    if (isEmptyChar(top)) {
        handleError("Stack is empty");
    }
    return top->data;
}

int isEmptyChar(node* top) {
    return top == NULL;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isRightAssociative(char op) {
    return op == '^';
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

void infixToPostfix(const char* infix, char* postfix) {
    node* opStack = NULL; 
    int k = 0; 

    for (int i = 0; infix[i]; i++) {
        char c = infix[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--;
        } else if (c == '(') {
            pushChar(&opStack, c);
        } else if (c == ')') {
            while (!isEmptyChar(opStack) && peekChar(opStack) != '(') {
                postfix[k++] = popChar(&opStack);
                postfix[k++] = ' ';
            }
            if (!isEmptyChar(opStack) && peekChar(opStack) == '(') {
                popChar(&opStack);
            } else {
                handleError("Mismatched parentheses");
            }
        } else if (isOperator(c)) {
            while (!isEmptyChar(opStack) && precedence(peekChar(opStack)) > precedence(c)) {
                postfix[k++] = popChar(&opStack);
                postfix[k++] = ' ';
            }
            if (!isEmptyChar(opStack) && precedence(peekChar(opStack)) == precedence(c) && !isRightAssociative(c)) {
                postfix[k++] = popChar(&opStack);
                postfix[k++] = ' ';
            }
            pushChar(&opStack, c);
        } else {
            handleError("Invalid character in the expression");
        }
    }

    while (!isEmptyChar(opStack)) {
        postfix[k++] = popChar(&opStack);
        postfix[k++] = ' ';
    }
    postfix[k - 1] = '\0';
}

void handleError(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main() {
    char infix[100];
    char postfix[100];

    printf("Enter an infix expression: ");
    if (fgets(infix, sizeof(infix), stdin) == NULL) {
        handleError("Error reading input");
    }

    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
