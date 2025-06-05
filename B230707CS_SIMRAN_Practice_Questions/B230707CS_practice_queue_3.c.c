#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue {
    int front, rear, size;
    int capacity;
    int* array;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

void enqueue(Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int front(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->array[queue->front];
}
typedef struct Stack {
    Queue* queue1;
    Queue* queue2;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->queue1 = createQueue(capacity);
    stack->queue2 = createQueue(capacity);
    return stack;
}

void push(Stack* stack, int item) {
    enqueue(stack->queue2, item);
    
    // Move all elements from queue1 to queue2
    while (!isEmpty(stack->queue1)) {
        enqueue(stack->queue2, dequeue(stack->queue1));
    }
    
    // Swap the names of the two queues
    Queue* temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
}

int pop(Stack* stack) {
    if (isEmpty(stack->queue1)) {
        printf("Stack is empty\n");
        return -1;
    }
    return dequeue(stack->queue1);
}

int top(Stack* stack) {
    if (isEmpty(stack->queue1)) {
        printf("Stack is empty\n");
        return -1;
    }
    return front(stack->queue1);
}

int isStackEmpty(Stack* stack) {
    return isEmpty(stack->queue1);
}
int main(){
    int num;
    char st;
    Stack* stack = createStack(MAX); 
    do{
        scanf("%c",&st);
        switch(st){
            case 'a': scanf("%d",&num);
                    push(stack,num);
                    break;
            case 'b':printf("%d",pop(stack));
                    break;
        }
    }while(st!='e');
}