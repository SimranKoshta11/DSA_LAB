#include <stdio.h>
#include <stdlib.h>
struct Queue{
    int front,rear,size;
    int capacity;
    int *arr;
};
typedef struct Queue* node;
node CreateQueue(int capacity){
    node queue=(node)malloc(sizeof(struct Queue));
    queue->capacity=capacity;
    queue->front=0;
    queue->size=0;
    queue->rear=capacity-1;
    queue->arr=(int*)malloc(queue->capacity*sizeof(int));
    return queue;
}
int isFull(node queue){
    if(queue->size==queue->capacity)
        return 1;
    return 0;
}
int isEmpty(node queue){
    if(queue->size==0)
        return 1;
    return 0;
}
void enqueue(node *queue,int data){
    if(isFull(*queue)){
        return;
    }
    (*queue)->rear=((*queue)->rear+1)%(*queue)->capacity;
    (*queue)->arr[(*queue)->rear]=data;
    (*queue)->size=(*queue)->size+1;
}
void dequeue(node *queue){
    if(isEmpty(*queue))
        return;
    int p=(*queue)->arr[(*queue)->front];
    (*queue)->front=((*queue)->front+1)%(*queue)->capacity;
    (*queue)->size=(*queue)->size-1;
}
int front(node queue){
    if(isEmpty(queue))
        return 0;
    return queue->arr[queue->front];
}
int rear(node queue){
    if(isEmpty(queue)){
        return 0;
    }
    return queue->arr[queue->rear];
}
void display(node queue){
    int count=queue->size;
    int i=queue->front;
    while (count > 0) {
        printf("%d ", queue->arr[i]);
        i = (i + 1) % queue->capacity;
        count--;
    }
}
int main(){
    int n,num;
    scanf("%d",&n);
    char st;
    node queue=CreateQueue(n);
    do{
        scanf("%c",&st);
        switch(st){
            case 'a': scanf("%d",&num);
                    enqueue(&queue,num);
                    break;
            case 'b':dequeue(&queue);
                    break;
            case 'c':display(queue);
                    break;
            case 'd': printf("%d",front(queue));
                    break;
            case 'e': printf("%d",rear(queue));
                    break;
        }
    }while(st!='f');
    return 0;
}