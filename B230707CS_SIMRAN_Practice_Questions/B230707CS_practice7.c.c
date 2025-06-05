#include <stdio.h>
#include <stdlib.h>

struct linkedlist{
    int data;
    struct linkedlist* next;
};
typedef struct linkedlist* node;
node CreateNode(int key){
    node temp=(node)malloc(sizeof(struct linkedlist));
    if(temp==NULL){
        printf("Error\n");
    }
    else{
        temp->data=key;
        temp->next=NULL;
    }
    return temp;
}
void insert(node *head,int key){
    node temp=CreateNode(key);
    if(*head==NULL){
        *head=temp;
    }
    else{
        node x=*head;
        while(x->next!=NULL){
            x=x->next;
        }
        x->next=temp;
    }
}
void selectionSort(node *head){
    node temp=*head;
    while(temp!=NULL){
        node r=temp->next;
        node min=temp;
        while(r!=NULL){
            if(r->data<min->data)
                min=r;
            r=r->next;
        }
        int tmp=temp->data;
        temp->data=min->data;
        min->data=tmp;
        temp=temp->next;
    }
}
void display(node head){
    node x=head;
    while(x!=NULL){
        printf("%d ",x->data);
        x=x->next;
    }
}
int main(){
    node head=NULL;
    char st;
    int num;
    do{
        scanf("%c",&st);
        if(st=='a'){
            scanf("%d",&num);
            insert(&head,num);
        }
    }while(st!='e');
    selectionSort(&head);
    display(head);
    return 0;
}