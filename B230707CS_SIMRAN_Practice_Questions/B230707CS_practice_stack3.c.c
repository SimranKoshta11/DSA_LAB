#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
struct Stack {
    int top;
    int capacity;
    int* arr;
};
typedef struct Stack* node;

node CreateStack(int capacity) {
    node stack = (node)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->arr = (int*)malloc(capacity * sizeof(int));
    return stack;
}

int isFull(node stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(node stack) {
    return stack->top == -1;
}

void push(node stack, int key) {
    if (isFull(stack)) {
        return;
    }
    stack->arr[++stack->top] = key;
}


int pop(node stack) {
    if (isEmpty(stack)) {
        return -1; 
    }
    return stack->arr[stack->top--];
}


int evaluatePostfix(char* expression) {
    node stack = CreateStack(50);
    if (!stack) return -1;

    for (int i = 0; expression[i]; i++) {
        if (isdigit(expression[i])) {
            push(stack, expression[i] - '0');
        } else {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (expression[i]) {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2 / val1); break;
                case '^': push(stack, (int)pow(val2, val1)); break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char str[50];
    scanf("%s", str);
    int result = evaluatePostfix(str);
    printf("%d\n", result);
    return 0;
}
