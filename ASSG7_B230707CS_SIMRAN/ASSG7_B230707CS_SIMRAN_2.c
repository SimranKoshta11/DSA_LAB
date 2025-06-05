#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct edges{
    int data;
    struct edges* next;
};
typedef struct edges* edge;
edge createedge(int key){
    edge tmp=(edge)malloc(sizeof(struct edges));
    tmp->data=key;
    tmp->next=NULL;
    return tmp;
}
void addedge(edge adj[],int u,int v){
    edge tmp=createedge(v);
    if(adj[u]==NULL){
        adj[u]=tmp;
        return ;
    }
    edge x=adj[u];
    while(x->next!=NULL)
        x=x->next;
    x->next=tmp;
}
struct Node{
    int adjc;
    int wt;
    struct Node* next;
};
typedef struct Node* node;
node createnode(int a,int b){
    node tmp=(node)malloc(sizeof(struct Node));
    tmp->adjc=a;
    tmp->wt=b;
    tmp->next=NULL;
    return tmp;
}
void insert(node adj[],int u,int v,int x){
    node tmp=createnode(v,x);
    tmp->next=adj[u];
    adj[u]=tmp;
}
int findPar(int it,int parent[]){
    if(it==parent[it])
        return it;
    return parent[it]=findPar(parent[it],parent);
}
void unionBySize(int u,int v,int size[],int parent[]){
    int ulp_u=findPar(u,parent);
    int ulp_v=findPar(v,parent);
    if(ulp_u==ulp_v)
        return ;
    if(size[ulp_u]<size[ulp_v]){
        parent[ulp_u]=ulp_v;
        size[ulp_v]=size[ulp_v]+size[ulp_u];
    }
    else{
        parent[ulp_v]=ulp_u;
        size[ulp_u]=size[ulp_u]+size[ulp_v];
    }
}
void swap(int** arr,int i,int j){
    int* tmp=arr[i]; 
    arr[i]=arr[j];
    arr[j]=tmp;
}
int main(){
    int n,start=-1;
    scanf("%d",&n);
    edge a[n];
    for(int i=0; i<n; i++)
        a[i]=NULL;
    for(int i=0; i<n; i++){
        int u=-1,j=0;
        char str[50];
        scanf(" %[^\n]",str);
        while(j<strlen(str)){
            int x=0;
            while(isdigit(str[j])){
                x=x*10+(str[j]-'0');
                j++;
            }
            j++;
            if(start==-1)
                start=x;
            if(u==-1)
                u=x;
            else{
                if(start==0)
                    addedge(a,u,x);
                else
                    addedge(a,u-1,x-1);
            }
        }
    }
    node adj[n];
    for(int i=0; i<n; i++)
        adj[i]=NULL;
    start=-1;
    for(int i=0; i<n; i++){
        int u=-1,j=0;
        char str[50];
        edge tmp;
        scanf(" %[^\n]",str);
        while(j<strlen(str)){
            int x=0;
            while(isdigit(str[j])){
                x=x*10+(str[j]-'0');
                j++;
            }
            j++;
            if(start==-1)
                start=x;
            if(u==-1){
                u=x;
                tmp=a[u-start];
            }
            else{
                if(start==0){
                    if(tmp!=NULL){
                        insert(adj,u,tmp->data,x);
                        tmp=tmp->next;
                    }
                }
                else{
                    if(tmp!=NULL){
                        insert(adj,u-1,tmp->data,x);
                        tmp=tmp->next;
                    }
                }
            }
        }
    }
    int dist[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            dist[i][j]=0;
        }
    }
    int** arr=(int**)malloc(100*sizeof(int*));
    for(int i=0; i<100; i++){
        arr[i]=(int*)malloc(3*sizeof(int));
    }
    int k=0;
    for(int i=0; i<n; i++){
        node tmp=adj[i];
        while(tmp!=NULL){
            if(!dist[i][tmp->adjc]){
                dist[i][tmp->adjc]=1;
                dist[tmp->adjc][i]=1;
                arr[k][0]=tmp->wt;
                arr[k][1]=i;
                arr[k][2]=tmp->adjc;
                k++;
            }
            tmp=tmp->next;
        }
    }
    int parent[n],size[n];
    for(int i=0; i<n; i++){
        parent[i]=i;
        size[i]=1;
    }
    for(int i=0; i<k; i++){
        for(int j=0; j<k-i-1; j++){
            if(arr[j][0]>arr[j+1][0]){
                swap(arr,j,j+1);
            }
        }
    }
    int mstwt=0;
    for(int i=0; i<k; i++){
        int weight=arr[i][0];
        int u=arr[i][1];
        int v=arr[i][2];
        if(findPar(u,parent)!=findPar(v,parent)){
            mstwt=mstwt+weight;
            unionBySize(u,v,size,parent);
        }
    }
    printf("%d\n",mstwt);
}