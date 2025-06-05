#include <stdio.h>
#include <stdlib.h>
struct Stack{
    int data;
    struct Stack* next;
};
typedef struct Stack* node;
node CreateNode(int data){
    node temp=(node)malloc(sizeof(struct Stack));
    temp->data=data;
    temp->next=NULL;
    return temp;
}
int isEmpty(node top){
    if(top==NULL)
        return 1;
    return 0;
}
void push(node *top,int data){
    node temp=CreateNode(data);
    temp->next=*top;
    *top=temp;
}
void pop(node *top){
    if(isEmpty(*top)){
        return ;
    }
    node temp=*top;
    *top=(*top)->next;
    free(temp);
}
int peek(node top){
    return top->data;
}
void display(node top){
    node temp=top;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
}
int main(){
    int num;
    char st;
    node top=NULL;
    do{
        scanf("%c",&st);
        switch(st){
            case 'a': scanf("%d",&num);
                    push(&top,num);
                    break;
            case 'b':pop(&top);
                    break;
            case 'c':display(top);
                    break;
            case 'd': printf("%d",peek(top));
                    break;
        }
    }while(st!='e');
    return 0;
}