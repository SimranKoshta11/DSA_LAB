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
void inputhead(node* head){
    char st;
    int num;
    while(scanf("%c",&st) && st!='e'){
        if (scanf("%d", &num) == 1) {
            insert(head, num);
        }
    }
}
node merging(node head1, node head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    node head = NULL, tail = NULL;

    if (head1->data < head2->data) {
        head = tail = head1;
        head1 = head1->next;
    } else {
        head = tail = head2;
        head2 = head2->next;
    }

    while (head1 && head2) {
        if (head1->data < head2->data) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }

    if (head1) tail->next = head1;
    if (head2) tail->next = head2;

    return head;
}
void display(node head){
    node x=head;
    while(x!=NULL){
        printf("%d ",x->data);
        x=x->next;
    }
}
int main(){
    node head1=NULL;
    node head2=NULL;
    inputhead(&head1);
    inputhead(&head2);
    node head=merging(head1,head2);
    display(head);
    return 0;
}