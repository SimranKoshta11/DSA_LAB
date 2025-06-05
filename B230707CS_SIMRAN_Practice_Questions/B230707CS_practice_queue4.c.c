#include <stdio.h>
#include <stdlib.h>
struct Stack {
    int data;
    struct Stack* next;
};
typedef struct Stack* node;

node CreateNode(int data) {
    node temp = (node)malloc(sizeof(struct Stack));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int isEmpty(node top) {
    return top == NULL;
}

void push(node* top, int data) {
    node temp = CreateNode(data);
    temp->next = *top;
    *top = temp;
}

int pop(node* top) {
    if (isEmpty(*top)) {
        return -1;
    }
    node temp = *top;
    *top = (*top)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}


int peek(node top) {
    if (isEmpty(top)) {
        return -1;
    }
    return top->data;
}

void display(node top) {
    node temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Queue {
    node stack1;
    node stack2;
};
typedef struct Queue* Q;


Q CreateQueue() {
    Q q = (Q)malloc(sizeof(struct Queue));
    q->stack1 = NULL;
    q->stack2 = NULL;
    return q;
}

void enqueue(Q queue, int data) {
    push(&(queue->stack1), data);
    
}

int dequeue(Q queue) {
    if (isEmpty(queue->stack1) && isEmpty(queue->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }
    
   
    if (isEmpty(queue->stack2)) {
        while (!isEmpty(queue->stack1)) {
            push(&(queue->stack2), pop(&(queue->stack1)));
        }
    }
    
    int data = pop(&(queue->stack2));
    printf("Dequeued %d\n", data);
    return data;
}

int main() {
    int num;
    char st;
    Q queue = CreateQueue();

    do {
        scanf(" %c", &st); 
        switch (st) {
            case 'a':
                scanf("%d", &num);
                enqueue(queue, num);
                break;
            case 'b':
                dequeue(queue);
                break;
            case 'c':
                printf("Queue elements: ");
                if (!isEmpty(queue->stack2)) {
                    display(queue->stack2);
                }
                if (!isEmpty(queue->stack1)) {
                    display(queue->stack1);
                }
                break;
        }
    } while (st != 'e');

    return 0;
}
