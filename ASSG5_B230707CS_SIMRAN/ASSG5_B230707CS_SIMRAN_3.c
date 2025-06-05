#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int data;
    struct Node *next;
};
typedef struct Node* node;
node createnode(int key){
    node temp=(node)malloc(sizeof(struct Node));
    temp->data=key;
    temp->next=NULL;
    return temp;
}
void addedge(node adj[],int u,int v){
    node tmp=createnode(v);
    tmp->next=adj[u];
    adj[u]=tmp;
}
int dfsCycle(int v,int vis[],int path[],node adj[]){
    vis[v]=1;
    path[v]=1;
    node tmp=adj[v];
    while(tmp!=NULL){
        int it=tmp->data;
        if(!vis[it]){
            if(dfsCycle(it,vis,path,adj))
                return 1;
        }
        else if(path[it])
            return 1;
        tmp=tmp->next;
    }
    path[v]=0;
    return 0;
}
void isDAG(node adj[],int n){
    int vis[n],path[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
        path[i]=0;
    }
    for(int i=0; i<n; i++){
        if(!vis[i]){
            if(dfsCycle(i,vis,path,adj)){
                printf("-1\n");
                return ;
            }
        }
    }
    printf("1\n");
}
void dfs1(int i,int vis[],node adj[]){
    vis[i]=1;
    node tmp=adj[i];
    while(tmp!=NULL){
        if(!vis[tmp->data]){
            dfs1(tmp->data,vis,adj);
        }
        tmp=tmp->next;
    }
}
void dfs(int i,int vis[],node adj[],int st[],int *j){
    vis[i]=1;
    node tmp=adj[i];
    while(tmp!=NULL){
        if(!vis[tmp->data]){
            dfs(tmp->data,vis,adj,st,j);
        }
        tmp=tmp->next;
    }
    st[(*j)++]=i;
}
void countStronglyConnectedComponents(node adj[],int n){
    int vis[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
    }
    int st[n],j=0;
    for(int i=0; i<n; i++){
        if(!vis[i]){
            dfs(i,vis,adj,st,&j);
        }
    }
    node rev[n];
    for(int i=0; i<n; i++){
        rev[i]=NULL;
    }
    for(int i=0; i<n; i++){
        node tmp=adj[i];
        while(tmp!=NULL){
            addedge(rev,tmp->data,i);
            tmp=tmp->next;
        }
    }
    int scc=0;
    for(int i=0; i<n; i++){
        vis[i]=0;
    }
    while(j>0){
        int p=st[--j];
        if(!vis[p]){
            scc++;
            dfs1(p,vis,rev);
        }
    }
    printf("%d\n",scc);
}
int main(){
    int n,m,u,v,index_offset=0;
    scanf("%d %d",&n,&m);
    node adj[n];
    for(int i=0; i<n; i++){
        adj[i]=NULL;
    }
    char buffer[1024];
    for (int i = 0; i < n; i++) {
        scanf(" %[^\n]", buffer);
        char *token = strtok(buffer, " ");
        u = atoi(token) - 1; 
        while ((token = strtok(NULL, " ")) != NULL) {
            v = atoi(token) - 1;  
            addedge(adj, u, v);
        }
    }
    char choice;
    do{
        scanf(" %c",&choice);
        switch(choice){
            case 'a':isDAG(adj,n);
                    break;
            case 'b':countStronglyConnectedComponents(adj,n);
                    break;
        }
    }while(choice!='x');
    for (int i = 0; i < n; i++) {
        node tmp;
        while (adj[i] != NULL) {
            tmp = adj[i];
            adj[i] = adj[i]->next;
            free(tmp);
        }
    }
}