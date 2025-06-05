#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct Node{
    int data;
    int height;
    struct Node* left;
    struct Node* right;
};
typedef struct Node* node;
node Create_Node(int key){
    node temp=(node)malloc(sizeof(struct Node));
    temp->data=key;
    temp->height=1;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void skip_spaces(char** str){
    while(isspace(**str))
        (*str)++;
}
node paren(char** str){
    skip_spaces(str);
    if(**str=='\0')
        return NULL;
    int num=0;
    int sign=1;
    if(**str=='-'){
        sign=-1;
        (*str)++;
    }
    while(isdigit(**str)){
        num=num*10+(**str-'0');
        (*str)++;
    }
    num=num*sign;
    node temp=Create_Node(num);
    skip_spaces(str);
    if(**str=='('){
        (*str)++;
        skip_spaces(str);
        if(**str==')'){
            (*str)++;
        }
        else{
            temp->left=paren(str);
            skip_spaces(str);
            if(**str==')'){
                (*str)++;
            }
        }
    }
    skip_spaces(str);
    if(**str=='('){
        (*str)++;
        skip_spaces(str);
        if(**str==')'){
            (*str)++;
        }
        else{
            temp->right=paren(str);
            skip_spaces(str);
            if(**str==')'){
                (*str)++;
            }
        }
    }
    return temp;
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
node insert(node root,int key){
    if(root==NULL)
        return Create_Node(key);
    if(key<root->data)
        root->left=insert(root->left,key);
    else if(key>root->data)
        root->right=insert(root->right,key);
    else
        return root;
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
void PrintRes(node root){
    if(root){
        if(root->left==NULL && root->right==NULL){
            printf("%d ",root->data);
            return ;
        }
            printf("%d ( ",root->data);
            PrintRes(root->left);
            printf(") ( ");
            PrintRes(root->right);
            printf(") ");
    }
}
node AVL_SeqInsert(node root,int n){
    root=insert(root,n);
    return root;
}
node search(node root,int key){
    node x=root;
    while(x!=NULL && x->data!=key){
        if(x->data>key)
            x=x->left;
        else
            x=x->right;
    }
    return x;
}
node successor(node root,int key){
    node x=search(root,key);
    if(x->right!=NULL){
        node temp=x->right;
        while(temp->left!=NULL)
            temp=temp->left;
        return temp;
    }
    node curr=root;
    node prev=NULL;
    while(curr!=NULL){
        if(curr->data>key){
            prev=curr;
            curr=curr->left;
        }
        else if(curr->data<key)
            curr=curr->right;
        else
            break;
    }
    return prev;
}
node predecessor(node root,int key){
    node x=search(root,key);
    if(x->left!=NULL){
        node temp=x->left;
        while(temp->right!=NULL)
            temp=temp->right;
        return temp;
    }
    node curr=root;
    node prev=NULL;
    while(curr!=NULL){
        if(curr->data<key){
            prev=curr;
            curr=curr->right;
        }
        else if(curr->data>key)
            curr=curr->left;
        else
            break;
    }
    return prev;
}
void PreOrder(node root){
    if(root){
        printf("%d ",root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}
node delete(node root,int key){
    if(root==NULL)
        return root;
    if(root->data==key){
        if(root->left==NULL || root->right==NULL){
            node temp=root->left ? root->left : root->right;
            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            else{
                *root=*temp;
            }
            free(temp);
        }
        else{
            node x=root->right;
            while(x->left!=NULL)
                x=x->left;
            root->data=x->data;
            root->right=delete(root->right,x->data);
        }
    }
    else if(root->data>key)
        root->left=delete(root->left,key);
    else
        root->right=delete(root->right,key);
    if(root==NULL)
        return root;
    root->height=max(height(root->left),height(root->right))+1;
    int balance=get_balance(root);
    if(balance>1 && get_balance(root->left)>=0)
        return right_rotation(root);
    if(balance>1 && get_balance(root->left)<0){
        root->left=left_rotation(root->left);
        return right_rotation(root);
    }
    if(balance<-1 && get_balance(root->right)<=0)
        return left_rotation(root);
    if(balance<-1 && get_balance(root->right)>0){
        root->right=right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}
node AVL_RangeDelete(node root,int n1,int n2){
    node x=search(root,n1);
    int s=0;
    if(x==NULL){
       x=successor(root,n1);
    }
    while(x!=NULL && x->data<n2){
        node succ=successor(root,x->data);
        root=delete(root,x->data);
        s++;
        x=succ;
    }
    node y=search(root,n2);
    if(y){
        root=delete(root,y->data);
        s++;
    }
    if(s==0)
        printf("-1\n");
    else{
        printf("%d ",s);
        PreOrder(root);
        printf("\n");
    }
    return root;
}
void PrintPath(node root,node x,int* arr,int *i){
    if(root==NULL)
        return ;
    arr[(*i)++]=root->data;
    if(root->data==x->data){
        for(int j=0; j<(*i); j++){
            printf("%d ",arr[j]);
        }
    }
    else{
        PrintPath(root->left,x,arr,i);
        PrintPath(root->right,x,arr,i);
    }
    (*i)--;
}
void AVL_SuccessorPath(node root,int key){
    node y=search(root,key);
    node x=successor(root,key);
    if(y==NULL || x==NULL)
        printf("%d\n",height(root)-1);
    else{
        int* arr=(int*)malloc(((root->height)+1)*sizeof(int));
        int i=0;
        PrintPath(root,x,arr,&i);
        printf("\n");
    }
}
void path(node root,int *sum){
    if(root){
        path(root->left,sum);
        (*sum)=(*sum)+root->data;
        path(root->right,sum);
    }
}
void AVL_SubtreeSum(node root,int key){
    node x=search(root,key);
    if(x){
        int sum=0;
        path(x,&sum);
        printf("%d ",sum);
        PrintRes(x);
        printf("\n");
    }
    else{
        printf("-1\n");
    }
}
int abs1(int a,int b){
    return (a-b)>0 ? a-b : b-a;
}
void AVL_FindClosest(node root,int key){
    node x=search(root,key);
    if(!x)
        printf("-1\n");
    else{
        node s=successor(root,key);
        node p=predecessor(root,key);
        int s1,p1;
        if(s)
            s1=abs1(s->data,x->data);
        if(p)
            p1=abs1(p->data,x->data);
        if(s!=NULL && p!=NULL){
            if(s1==p1){
                if(s->data<p->data)
                    printf("%d\n",s->data);
                else
                    printf("%d\n",p->data);
            }
            else if(s1<p1)
                printf("%d\n",s->data);
            else
                printf("%d\n",p->data);
        }
        else if(s==NULL)
            printf("%d\n",p->data);
        else if(p==NULL)
            printf("%d\n",s->data);
        else
            printf("-1\n");
    }
}
int main(){
    char str[100];
    fgets(str,sizeof(str),stdin);
    char* p=str;
    node root=paren(&p);
    int num,n1,n2,i,num1;
    char choice;
    char s[100];
    do{
        scanf("%c",&choice);
        switch(choice){
            case 'a':fgets(s,sizeof(s),stdin);
                    i=0;
                    while(i<strlen(s)){
                        num1=0;
                        while(isdigit(s[i])){
                            num1=num1*10+(int)(s[i]-'0');
                            i++;
                        }
                        if(num1!=0)
                            root=AVL_SeqInsert(root,num1);
                        i++;
                    }
                    PrintRes(root);
                    printf("\n");
                    break;
            case 'b':scanf("%d %d",&n1,&n2);
                    root=AVL_RangeDelete(root,n1,n2);
                    break;
            case 'c':scanf("%d",&num);
                    AVL_SuccessorPath(root,num);
                    break;
            case 'd':scanf("%d",&num);
                    AVL_SubtreeSum(root,num);
                    break;
            case 'e':scanf("%d",&num);
                    AVL_FindClosest(root,num);
                    break;
        }
    }while(choice!='g');
}