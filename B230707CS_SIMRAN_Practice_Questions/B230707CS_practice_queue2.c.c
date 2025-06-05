#include <stdio.h>
#include <stdlib.h>
struct Queue{
    int data;
    struct Queue* next;
};
typedef struct Queue* node;
node CreateNode(int k){
    node temp=(node)malloc(sizeof(struct Queue));
    temp->data=k;
    temp->next=NULL;
    return temp;
}
void push(node *rear,node *front,int data){
    node temp=CreateNode(data);
    if(*front==NULL && *rear==NULL)
        *front=*rear=temp;
    else{
        (*rear)->next=temp;
        *rear=temp;
    }
}
void pop(node *rear,node *front){
    if(*front!=NULL){
        node temp=*front;
        (*front)=(*front)->next;
        free(temp);
    }
}
int front1(node front){
    if(front!=NULL)
        return front->data;
    return 0;
}
int rear1(node rear){
    if(rear!=NULL)
        return rear->data;
    return 0;
}
void display(node front){
    while(front!=NULL){
        printf("%d ",front->data);
        front=front->next;
    }
}
int main(){
    int num;
    char st;
    node front=NULL;
    node rear=NULL;
    do{
        scanf("%c",&st);
        switch(st){
            case 'a': scanf("%d",&num);
                    push(&rear,&front,num);
                    break;
            case 'b':pop(&rear,&front);
                    break;
            case 'c':display(front);
                    break;
            case 'd': printf("%d",front1(front));
                    break;
            case 'e': printf("%d",rear1(rear));
                    break;
        }
    }while(st!='f');
    return 0;
}