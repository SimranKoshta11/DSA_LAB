#include <stdio.h>
#include <stdlib.h>
int bipartite(int node,int n,int **mat,int color[]){
    int queue[n],rear=0,front=0;
    color[node]=0;
    queue[rear++]=node;
    int temp;
    while(front<rear){
        temp=queue[front++];
        for(int i=0; i<n; i++){
            if(mat[temp][i]==1){
                if(color[i]==-1){
                    color[i]=!color[temp];
                    queue[rear++]=i;
                }
                else if(color[i]==color[temp])
                    return 0;
            }
        }
    }
    return 1;
}
void isBipartite(int **mat,int n){
    int color[n];
    for(int i=0; i<n; i++){
        color[i]=-1;
    }
    for(int i=0; i<n; i++){
        if(color[i]==-1){
            if(bipartite(i,n,mat,color)==0){
                printf("-1\n");
                return ;
            }
        }
    }
    printf("1\n");
}
int cycle(int node,int vis[],int **mat,int n){
    int queue[n][2],rear=0,front=0;
    vis[node]=1;
    queue[rear][0]=node;
    queue[rear][1]=-1;
    rear++;
    int temp,temppar;
    while(front<rear){
        temp=queue[front][0];
        temppar=queue[front][1];
        front++;
        for(int i=0; i<n; i++){
            if(mat[temp][i]==1){
                if(!vis[i]){
                    vis[i]=1;
                    queue[rear][0]=i;
                    queue[rear][1]=temp;
                    rear++;
                }
                else if(i!=temppar){
                    return 1;
                }
            }
        }
    }
    return 0;
}
void hasCycle(int **mat,int n){
    int vis[n];
    for(int i=0;i<n; i++){
        vis[i]=0;
    }
    for(int i=0; i<n; i++){
        if(!vis[i]){
            if(cycle(i,vis,mat,n)==1){
                printf("1\n");
                return ;
            }
        }
    }
    printf("-1\n");
}
void bfs(int node,int n,int **mat,int vis[]){
    int queue[n],rear=0,front=0;
    vis[node]=1;
    queue[rear++]=node;
    int tmp;
    while(front<rear){
        tmp=queue[front++];
        for(int i=0; i<n; i++){
            if(mat[tmp][i]==1){
                if(!vis[i]){
                    vis[i]=1;
                    queue[rear++]=i;
                }
            }
        }
    }
}
void isTree(int **mat,int n){
    int vis[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
    }
    int cnt=0,c=0;
    for(int i=0; i<n; i++){
        if(!vis[i]){
            bfs(i,n,mat,vis);
            cnt++;
        }
    }
    for(int i=0;i<n; i++){
        vis[i]=0;
    }
    for(int i=0; i<n; i++){
        if(!vis[i]){
            if(cycle(i,vis,mat,n)==1){
                c=1;
                break;
            }
        }
    }
    if(cnt==1 && c==0){
        printf("1\n");
    }
    else{
        printf("-1\n");
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int **mat=(int **)malloc(n*sizeof(int *));
    for(int i=0; i<n; i++){
        mat[i]=(int *)malloc(n*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d",&mat[i][j]);
        }
    }
    char choice;
    do{
        scanf("%c",&choice);
        switch(choice){
            case 'a':isBipartite(mat,n);
                    break;
            case 'b':hasCycle(mat,n);
                    break;
            case 'c':isTree(mat,n);
                    break;
        }
    }while(choice!='x');
}