#include <stdio.h>
#include <stdlib.h>
int min(int a,int b){
    return a<b ? a: b;
}
void dfs(int **mat,int vis[],int node,int n){
    vis[node]=1;
    for(int i=0; i<n; i++){
        if(mat[i][node]==1){
            if(!vis[i]){
                dfs(mat,vis,i,n);
            }
        }
    }
}
void noOfConnectedComponents(int **mat,int n){
    int vis[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
    }
    int cnt=0;
    for(int i=0; i<n; i++){
        if(!vis[i]){
            dfs(mat,vis,i,n);
            cnt++;
        }
    }
    printf("%d\n",cnt);
}
void dfs1(int **mat,int vis[],int node,int n,int *c){
    vis[node]=1;
    (*c)++;
    for(int i=0; i<n; i++){
        if(mat[i][node]==1){
            if(!vis[i]){
                dfs1(mat,vis,i,n,c);
            }
        }
    }
}
void sizeOfComponents(int **mat,int n){
    int vis[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
    }
    int cnt;
    int* arr=(int*)malloc(n*sizeof(int));
    int j=0;
    for(int i=0; i<n; i++){
        if(!vis[i]){
            cnt=0;
            dfs1(mat,vis,i,n,&cnt);
            arr[j++]=cnt;
        }
    }
    for(int i=0; i<j; i++){
        for(int k=0; k<j-1-i; k++){
            if(arr[k]>arr[k+1]){
                int tmp=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=tmp;
            }
        }
    }
    for(int i=0; i<j; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void dfs2(int node,int parent,int vis[],int **mat,int tin[],int low[],int *c,int *timer,int n){
    vis[node]=1;
    tin[node]=low[node]=(*timer);
    (*timer)++;
    for(int i=0; i<n; i++){
        if(mat[i][node]==1){
            if(i==parent)
                continue;
            if(!vis[i]){
                dfs2(i,node,vis,mat,tin,low,c,timer,n);
                low[node]=min(low[node],low[i]);
                if(low[i]>tin[node])
                    (*c)++;
            }
            else    
                low[node]=min(low[node],low[i]);
        }
    }
}
void noOfBridges(int **mat,int n){
    int vis[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
    }
    int tin[n],low[n];
    int c=0,timer;
    for(int i=0; i<n; i++){
        if(!vis[i]){
            timer=0;
            dfs2(i,-1,vis,mat,tin,low,&c,&timer,n);
        }
    }
    printf("%d\n",c);
}
void dfs3(int node,int parent,int vis[],int **mat,int tin[],int low[],int mark[],int *timer,int n){
    vis[node]=1;
    tin[node]=low[node]=(*timer);
    (*timer)++;
    int child=0;
    for(int i=0; i<n; i++){
        if(mat[i][node]==1){
            if(i==parent)
                continue;
            if(!vis[i]){
                dfs3(i,node,vis,mat,tin,low,mark,timer,n);
                low[node]=min(low[node],low[i]);
                if(low[i]>=tin[node] && parent!=-1){
                    mark[node]=1;
                }
                child++;
            }
            else{
                low[node]=min(low[node],tin[i]);
            }
        }
    }
    if(child>1 && parent==-1)
        mark[node]=1;
}
void noOfArticulationPoints(int **mat,int n){
    int vis[n],mark[n];
    for(int i=0; i<n; i++){
        vis[i]=0;
        mark[i]=0;
    }
    int tin[n],low[n];
    int c=0,timer;
    for(int i=0; i<n; i++){
        if(!vis[i]){
            timer=0;
            dfs3(i,-1,vis,mat,tin,low,mark,&timer,n);
        }
    }
    for(int i=0; i<n; i++){
        if(mark[i]==1){
            c++;
        }
    }
    printf("%d\n",c);
}
int main(){
    int n;
    scanf("%d",&n);
    int** mat=(int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        mat[i]=(int*)malloc(n*sizeof(int));
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
            case 'a':noOfConnectedComponents(mat,n);
                    break;
            case 'b':sizeOfComponents(mat,n);
                    break;
            case 'c':noOfBridges(mat,n);
                    break;
            case 'd':noOfArticulationPoints(mat,n);
                    break;
        }
    }while(choice!='x');
}