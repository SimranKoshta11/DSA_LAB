#include <stdio.h>
#include <stdlib.h>
struct avlTree{
    int data;
    struct avlTree* left;
    struct avlTree* right;
    int height;
};
typedef struct avlTree* node;
node Create_Node(int key){
    node temp=(node)malloc(sizeof(struct avlTree));
    temp->data=key;
    temp->left=NULL;
    temp->right=NULL;
    temp->height=1;
    return temp;
}
int max(int a,int b){
    return a>b ? a: b;
}
int height(node x){
    if(x==NULL)
        return 0;
    return x->height;
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
int balance(node n){
    if(n==NULL)
        return 0;
    return height(n->left)-height(n->right);
}
node AVL_insert(node root,int key,int *lr,int *rr){
    if(root==NULL)
        return Create_Node(key);
    if(root->data>key)
        root->left=AVL_insert(root->left,key,lr,rr);
    else
        root->right=AVL_insert(root->right,key,lr,rr);
    root->height=1+max(height(root->left),height(root->right));
    int balance_fac=balance(root);
    if(balance_fac>1 && key<root->left->data){
        (*rr)++;
        root=right_rotation(root);
    }
    if(balance_fac<-1 && key>root->right->data){
        (*lr)++;
        root=left_rotation(root);
    }
    if(balance_fac>1 && key>root->left->data){
        (*lr)++;
        (*rr)++;
        root->left=left_rotation(root->left);
        return right_rotation(root->right);
    }
    if(balance_fac<-1 && key<root->right->data){
        (*lr)++;
        (*rr)++;
        root->right=right_rotation(root->right);
        return left_rotation(root->right);
    }
    return root;
}
node AVL_delete(node root,int key,int *lr,int *rr){
    if(root==NULL)
        return root;
    if(root->data>key)
        root->left=AVL_delete(root->left,key,lr,rr);
    else if(root->data<key)
        root->right=AVL_delete(root->right,key,lr,rr);
    else{
        if(root->left==NULL || root->right==NULL){
            node temp=root->left ? root->left :root->right;
            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            else
                *root=*temp;
            free(temp);
        }
        else{
            node r=root->right;
            while(r->left!=NULL)
                r=r->left;
            root->data=r->data;
            root->right=AVL_delete(root->right,r->data,lr,rr);
        }
    }
    if(root==NULL) return root;
    root->height=1+max(height(root->left),height(root->right));
    int balance_fac=balance(root);
    if(balance_fac>1 && balance(root->left)>=0){
        (*rr)++;
        return right_rotation(root);
    }
    if(balance_fac>1 && balance(root->left)<0){
        (*rr)++;
        (*lr)++;
        root->left=left_rotation(root->left);
        return right_rotation(root);
    }
    if(balance_fac<-1 && balance(root->right)<=0){
        (*lr)++;
        return left_rotation(root);
    }
    if(balance_fac<-1 && balance(root->right)>0){
        (*lr)++;
        (*rr)++;
        root->right=right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}
void find(node root,int key,int *arr,int *i,int d){
    if(root==NULL){
        return;
    }
    arr[(*i)++]=root->data;
    if(root->data==key){
        if(d){
            for(int j=0; j<(*i); j++){
                printf("%d ",arr[j]);
            }
            return;
        }
        else{
            for(int j=(*i)-1; j>=0; j--){
                printf("%d ",arr[j]);
            }
            return;
        }
    }
    find(root->left,key,arr,i,d);
    find(root->right,key,arr,i,d);
    (*i)--;
}
void AVL_find(node root,int key,int d){
    node x=root;
    while(x!=NULL && x->data!=key){
        if(x->data>key)
            x=x->left;
        else
            x=x->right;
    }
    if(x==NULL)
        printf("-1");
    else{
        int i=0;
        int* arr=(int*)malloc(200*sizeof(int));
        find(root,key,arr,&i,d);
    }

}
void AVL_postorder(node root){
    if(root){
        AVL_postorder(root->left);
        AVL_postorder(root->right);
        printf("%d ",root->data);
    }
}
void AVL_rotations(node root,int lr,int rr){
    printf("%d %d \n",lr,rr);
}
void AVL_balance(node root,int key){
    node x=root;
    while(x!=NULL && x->data!=key){
        if(x->data>key)
            x=x->left;
        else
            x=x->right;
    }
    if(x) 
        printf("%d\n",balance(x));
    else 
        printf("-1\n");
}
int main(){
    int n,rr=0,lr=0;
    char choice;
    node root=NULL;
    do{
        scanf("%c",&choice);
        switch(choice){
            case 'i':scanf("%d",&n);
                    root=AVL_insert(root,n,&lr,&rr);
                    break;
            case 'f':scanf("%d",&n);
                    AVL_find(root,n,1);
                    printf("\n");
                    break;
            case 'p':AVL_postorder(root);
                    printf("\n");
                    break;
            case 's':AVL_rotations(root,lr,rr);
                    break;
            case 'd':scanf("%d",&n);
                    AVL_find(root,n,0);
                    printf("\n");
                    root=AVL_delete(root,n,&lr,&rr);
                    break;
            case 'b':scanf("%d",&n);
                    AVL_balance(root,n);
                    break;
        }
    }while(choice!='e');
}