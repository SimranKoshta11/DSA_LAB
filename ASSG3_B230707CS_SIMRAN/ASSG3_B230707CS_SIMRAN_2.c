#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Node{
    int data;
    struct Node* next;
};
typedef struct Node* node;
node create(int key){
    node temp=(node)malloc(sizeof(struct Node));
    temp->data=key;
    temp->next=NULL;
    return temp;
}
void insert(node hash[],int key,int n){
    int i=key%n;
    node curr=hash[i];
    while(curr!=NULL){
        if(curr->data==key){
            printf("-1\n");
            return;
        }
        curr=curr->next;
    }
    node temp=create(key);
    temp->next=hash[i];
    hash[i]=temp;
    curr=hash[i];
    node index=NULL;
    while(curr!=NULL){
        index=curr->next;
        while(index!=NULL){
            if(curr->data>index->data){
                int k=curr->data;
                curr->data=index->data;
                index->data=k;
            }
            index=index->next;
        }
        curr=curr->next;
    }
}
void search(node hash[],int key,int n){
    int i=key%n;
    int c=1;
    node curr=hash[i];
    while(curr!=NULL){
        if(curr->data==key){
            printf("%d %d\n",i,c);
            return;
        }
        curr=curr->next;
        c++;
    }
    printf("-1\n");
}
void delete(node hash[],int key,int n){
    int i=key%n;
    int c=1;
    node curr=hash[i];
    node prev=NULL;
    while(curr!=NULL){
        if(curr->data==key){
            printf("%d %d\n",i,c);
            node temp=curr;
            if(prev==NULL){
                hash[i]=curr->next;
            }
            else{
                prev->next=curr->next;
            }
            free(temp);
            return;
        }
        prev=curr;
        curr=curr->next;
        c++;
    }
    printf("-1\n");
}
void update(node hash[],int ok,int nk,int n){
    int i=ok%n;
    int j=nk%n;
    int c=0,find=0,s=0;
    node curr=hash[i];
    while(curr!=NULL){
        if(curr->data==ok){
            find=1;
            break;
        }
        curr=curr->next;
    }
    curr=hash[j];
    while(curr!=NULL){
        if(curr->data==nk){
            s=1;
            break;
        }
        curr=curr->next;
    }
    if(find==0 || s==1){
        printf("-1\n");
        return;
    }
    delete(hash,ok,n);
    insert(hash,nk,n);
}
void printElementsInChain(node hash[],int index){
    node curr=hash[index];
    if(curr==NULL){
        printf("-1\n");
        return;
    }
    while(curr!=NULL){
        printf("%d ",curr->data);
        curr=curr->next;
    }
    printf("\n");
}
int main(){
    int n,a,b; 
    scanf("%d",&n);
    node hash[n];
    for(int i=0; i<n; i++){
        hash[i]=NULL;
    }
    char choice;
    do{
        scanf(" %c",&choice);
        switch(choice){
            case 'a': scanf("%d",&a);
                    insert(hash,a,n);
                    break;
            case 'b':scanf("%d",&a);
                    search(hash,a,n);
                    break;
            case 'c':scanf("%d",&a);
                    delete(hash,a,n);
                    break;
            case 'd': scanf("%d %d",&a,&b);
                    update(hash,a,b,n);
                    break;
            case 'e':scanf("%d",&a);
                    printElementsInChain(hash,a);
                    break;
        }
    }while(choice!='f');
}