#include <stdio.h>
#include <stdlib.h>
struct LinkedList{
	int data;
	struct LinkedList *next;
};
typedef struct LinkedList* node;
node CreateNode(int key){
	node temp=(node)malloc(sizeof( struct LinkedList));
	if(temp==NULL)
		return NULL;
	temp->data=key;
	temp->next=NULL;
	return temp;
}
void insert(node *head,int key){
	node temp=CreateNode(key);
	if(*head==NULL)
		*head=temp;
	else{
		node x=*head;
		while(x->next!=NULL){
			x=x->next;
		}
		x->next=temp;
	}
}
void delete(node *head){
	if(*head==NULL)
		return ;
	else{
		node temp=*head;
		*head=(*head)->next;
		free(temp);
	}
}
void display(node head){
	node x=head;
	while(x!=NULL){
		printf("%d ",x->data);
		x=x->next;
	}
}
void reverse(node *head){
	node curr=*head;
	node prev=NULL,next=NULL;
	while(curr!=NULL){
		next=curr->next;
		curr->next=prev;
		prev=curr;
		curr=next;
	}
	*head=prev;
}
int main(){
	char choice;
	int k;
	node head=NULL;
	do{
		scanf("%c",&choice);
		switch(choice){
			case 'a': scanf("%d",&k);
				insert(&head,k);
				break;
			case 'b': delete(&head);
				break;
			case 'c': display(head);
				break;
			case 'r':
				reverse(&head);
		}
	}while(choice!='d');
	return 0;
}
