#include <stdio.h>
#include <stdlib.h>
struct Node{
    int data;
    int height;
    int val;
    struct Node* left;
    struct Node* right;
};
typedef struct Node* node;
node Create_Node(int key,int value){
    node temp=(node)malloc(sizeof(struct Node));
    temp->data=key;
    temp->val=value;
    temp->height=1;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct OrderMap{
    node tnode;
    int size;
};
typedef struct OrderMap* map;
map Create_Map(){
    map m=(map)malloc(sizeof(struct OrderMap));
    m->tnode=NULL;
    m->size=0;
    return m;
}
int height(node n){
    if(n==NULL) return 0;
    return n->height;
}
int max(int a,int b){
    return a>b ? a: b;
}
int get_balance(node n){
    if(n==NULL) return 0;
    return height(n->left)-height(n->right);
}
node left_rotation(node x){
    node y=x->right;
    node t2=y->left;
    y->left=x;
    x->right=t2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}
node right_rotation(node x){
    node y=x->left;
    node t2=y->right;
    y->right=x;
    x->left=t2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}
node insert(node root,int key,int value){
    if(root==NULL)
        return Create_Node(key,value);
    if(root->data>key)
        root->left=insert(root->left,key,value);
    else if(root->data<key)
        root->right=insert(root->right,key,value);
    else{
        root->val=value;
        return root;
    }
    root->height=max(height(root->left),height(root->right))+1;
    int balance=get_balance(root);
    if(balance>1 && key<root->left->data)
        return right_rotation(root);
    if(balance>1 && key>root->left->data){
        root->left=left_rotation(root->left);
        return right_rotation(root);
    }
    if(balance<-1 && key>root->right->data)
        return left_rotation(root);
    if(balance<-1 && key<root->right->data){
        root->right=right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}
node search(node root,int key){
    while(root!=NULL && root->data!=key){
        if(root->data>key)
            root=root->left;
        else
            root=root->right;
    }
    return root;
}
node upper_bound(node root,int key){
    node current=root;
    node previous=NULL;
    while(current!=NULL){
        if(current->data>=key){
            previous=current;
            current=current->left;
        }
        else
            current=current->right;
    }
    return previous;
}
void display_element(node root){
    if(root){
        display_element(root->right);
        printf("%d ",root->data);
        display_element(root->left);
    }
}
void Insert(map *k,int key,int value){
    if(!search((*k)->tnode,key))
        (*k)->size++;
    (*k)->tnode=insert((*k)->tnode,key,value);
}
void UpperBound(map k,int key){
    node ub=upper_bound(k->tnode,key);
    if(ub)
        printf("%d %d\n",ub->data,ub->val);
    else
        printf("-1\n");
}
void Find(map k,int key){
    node temp=search(k->tnode,key);
    if(temp)
        printf("%d %d\n",temp->data,temp->val);
    else
        printf("-1\n");
}
void Size(map k){
    printf("%d\n",k->size);
}
void Empty(map k){
    if(k->size==0)
        printf("1\n");
    else
        printf("0\n");
}
void DisplayElements(map k){
    if(k->size==0) printf("-1\n");
    else{
        display_element(k->tnode);
        printf("\n");
    }
}
int main(){
    int key,value;
    char choice;
    map K=Create_Map();
    do{
        scanf("%c",&choice);
        switch(choice){
            case 'i':scanf("%d %d",&key,&value);
                    Insert(&K,key,value);
                    break;
            case 'u':scanf("%d",&key);
                    UpperBound(K,key);
                    break;
            case 'f':scanf("%d",&key);
                    Find(K,key);
                    break;
            case 's':Size(K);
                    break;
            case 'e':Empty(K);
                    break;
            case 'd':DisplayElements(K);
                    break;
        }
    }while(choice!='t');
}