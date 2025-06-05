#include <stdio.h>
#include <stdlib.h>
struct Stack{
    int top;
    int capacity;
    int* arr;
};
typedef struct Stack* node;
node CreateStack(int capacity){
    node stack=(node)malloc(sizeof(struct Stack));
    stack->top=-1;
    stack->arr=(int*)malloc(capacity*sizeof(int));
    return stack;
}
int isFull(node stack){
    if(stack->top==stack->capacity-1)
        return 1;
    return 0;
}
int isEmpty(node stack){
    if(stack->top==-1)
        return 1;
    return 0;
}
void push(node stack,int key){
    if(isFull(stack)){
        return;
    }
    stack->arr[++stack->top]=key;
}
void pop(node stack){
    if(isEmpty(stack)){
        return ;
    }
    stack->top--;
}
int peek(node stack){
    return stack->arr[stack->top];
}
void display(node stack){
    for(int i=0;i<=stack->top ; i++){
        printf("%d ",stack->arr[i]);
    }
}
void nextGreaterElement(int arr[], int n) {
    int *nge = (int *)malloc(n * sizeof(int));  
    node stack = CreateStack(n);

    for (int i = n - 1; i >= 0; i--) {
        while (!isEmpty(stack) && peek(stack) <= arr[i]) {
            pop(stack);
        }
        if (!isEmpty(stack)) {
            nge[i] = peek(stack);
        } else {
            nge[i] = -1;
        }
        push(stack, arr[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", nge[i]);
    }
    printf("\n");

    free(nge);
    free(stack->arr);
    free(stack);
}

int main(){
    int num;
    char st;
    int n;
    scanf("%d",&n);
    node stack=CreateStack(n);
    do{
        scanf("%c",&st);
        switch(st){
            case 'a': scanf("%d",&num);
                    push(stack,num);
                    break;
            case 'b':pop(stack);
                    break;
            case 'c':display(stack);
                    break;
            case 'd': printf("%d",peek(stack));
                    break;
        }
    }while(st!='e');
    nextGreaterElement(stack->arr,stack->top+1);
    return 0;
}