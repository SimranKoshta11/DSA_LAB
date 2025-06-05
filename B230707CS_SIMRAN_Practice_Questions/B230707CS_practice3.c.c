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
node insert(node head,int key){
	node temp=CreateNode(key);
	if(head==NULL)
		head=temp;
	else{
		
		node x=head;
		while(x->next!=NULL && x->data!=key){
			x=x->next;
		}
		node y=head;
		if(x->data==key){
			while(y->next!=NULL){
				y=y->next;
			}
			y->next=x;
			return head;
		}
		x->next=temp;
		return head;
	}
}
int detect(node head){
	node slow=head;
	node fast=head;
	while(fast!=NULL && fast->next!=NULL){
		slow=slow->next;
		fast=fast->next->next;
		if(slow==fast){
			return 1;
			slow=head;
			while(fast!=slow){
				fast=fast->next;
				slow=slow->next;
			}
			printf("%d",slow->data);
		}
	}
	return 0;
}

int main(){
	char choice;
	int k;
	node head=NULL;
	do{
		scanf("%c",&choice);
		switch(choice){
			case 'a': scanf("%d",&k);
				head=insert(head,k);
				break;
			case 'b': int l=detect(head);
				printf("%d",l);
				if(l){
				  	node slow=head;
					node fast=head;
					while(fast!=NULL && fast->next!=NULL){
						slow=slow->next;
						fast=fast->next->next;
						if(slow==fast){
							slow=head;
							while(fast!=slow){
								fast=fast->next;
								slow=slow->next;
							}
							printf(" %d",slow->data);
							break;
						}
					}
				  }
		                 break;
		}
	}while(choice!='d');
	return 0;
}
