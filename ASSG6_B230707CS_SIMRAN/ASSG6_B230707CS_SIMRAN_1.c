#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct line{
    int d;
    struct line* next;
};
typedef struct line* edge;
edge create_edge(int key){
    edge tmp=(edge)malloc(sizeof(struct line));
    tmp->d=key;
    tmp->next=NULL;
    return tmp;
}
struct ver{
    int a;
    int dis;
    struct ver* next;
};
typedef struct ver* vertex;
vertex create_vertex(int a,int dis){
    vertex tmp=(vertex)malloc(sizeof(struct ver));
    tmp->a=a;
    tmp->dis=dis;
    tmp->next=NULL;
    return tmp;
}
void addedge(edge l[],int u,int v){
    edge tmp=create_edge(v);
    if(l[u]==NULL){
        l[u]=tmp;
        return ;
    }
    edge x=l[u];
    while(x->next!=NULL)
        x=x->next;
    x->next=tmp;
}
void insert(vertex l[],int u,int v,int wt){
    vertex tmp=create_vertex(v,wt);
    tmp->next=l[u];
    l[u]=tmp;
}
void heapify(int **pq,int i,int n){
    int smll=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && pq[left][0]<pq[smll][0])
        smll=left;
    if(right<n && pq[right][0]<pq[smll][0])
        smll=right;
    if(smll!=i){
        int s=pq[smll][0];
        int p=pq[smll][1];
        pq[smll][0]=pq[i][0];
        pq[smll][1]=pq[i][1];
        pq[i][0]=s;
        pq[i][1]=p;
        heapify(pq,smll,n);
    }
}
void build(int **pq,int front,int rear){
    int n=(rear-front);
    for(int i=n/2-1; i>=front; i--)
        heapify(pq,i,n);
}
int main(){
    int n,start=-1;
    scanf("%d",&n);
    edge l[n];
    for(int i=0; i<n; i++)
        l[i]=NULL;
    for(int i=0; i<n; i++){
        char str[50];
        int u=-1;
        scanf(" %[^\n]",str);
        int j=0;
        while(j<strlen(str)){
            int x=0;
            while(isdigit(str[j])){
                x=x*10+(str[j]-'0');
                j++;
            }
            j++;
            if(start==-1){
                start=x;
            }
            if(u==-1)
                u=x;
            else {
                if(start==0)
                    addedge(l,u,x);
                else
                    addedge(l,u-1,x-1);
            }   
        }
    }
    vertex adj[n];
    start=-1;
    for(int i=0; i<n; i++)
        adj[i]=NULL;
    for(int i=0; i<n; i++){
        char str[50];
        int u=-1;
        scanf(" %[^\n]",str);
        int j=0;
        edge tmp;
        while(j<strlen(str)){
            int x=0;
            while(isdigit(str[j])){
                x=x*10+(str[j]-'0');
                j++;
            }
            j++;
            if(start==-1){
                start=x;
            }
            if(u==-1){
                u=x;
                tmp=l[u-start];
            }
            else{
                if(start==0){
                    if(tmp!=NULL){  
                        insert(adj,u,tmp->d,x);
                        tmp=tmp->next;
                    }
                }
                else{
                    if(tmp!=NULL){  
                        insert(adj,u-1,tmp->d,x);
                        tmp=tmp->next;
                    }
                }
            }
        }
    }
    int** pq=(int**)malloc(100*sizeof(int*));
    for(int i=0; i<100; i++){
        pq[i]=(int*)malloc(2*sizeof(int));
    }
    int s;
    scanf("%d",&s);
    s=s-start;
    int distance[n];
    for(int i=0; i<n; i++){
        distance[i]=100000;
    }
    distance[s]=0;
    int rear=0,front=0;
    pq[rear][0]=distance[s];
    pq[rear][1]=s;
    rear++;
    while(front<rear){
        build(pq,front,rear);
        int wt=pq[front][0];
        int node=pq[front][1];
        front++;
        vertex tmp=adj[node];
        while(tmp!=NULL){
            int adjacent=tmp->a;
            int weight=tmp->dis;
            if(wt+weight<distance[adjacent]){
                distance[adjacent]=wt+weight;
                pq[rear][0]=distance[adjacent];
                pq[rear][1]=adjacent;
                rear++;
            }
            tmp=tmp->next;
        }
    }
    for(int i=0; i<n; i++){
        printf("%d ",distance[i]);
    }
    printf("\n");
    return 0;
    for(int i=0; i<n; i++){
        free(pq[i]);
    }
}