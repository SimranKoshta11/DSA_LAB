#include <stdio.h>
#include <stdlib.h>
void swap(int **pq,int i,int j){
    int* tmp=pq[i]; 
    pq[i]=pq[j];
    pq[j]=tmp;
}
void heapify(int **pq,int n,int i){
    int smll=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && pq[left][0]<pq[smll][0])
        smll=left;
    if(right<n && pq[right][0]<pq[smll][0])
        smll=right;
    if(smll!=i){
        swap(pq,smll,i);
        heapify(pq,n,smll);
    }
}
void maintain(int** pq,int rear,int front){
    int n=rear-front;
    for(int i=n/2-1; i>=0; i--){
        heapify(pq+front,n,i);
    }
}
void Sequence(int** mat,int x,int n){
    int vis[n];
    for(int i=0; i<n; i++)
        vis[i]=0;
    int **pq=(int**)malloc(100*sizeof(int*));
    for(int i=0; i<100; i++){
        pq[i]=(int*)malloc(3*sizeof(int));
    }
    int **arr=(int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++)
        arr[i]=(int*)malloc(3*sizeof(int));
    int rear=0,front=0,j=0;
    pq[rear][0]=0;
    pq[rear][1]=x;
    pq[rear][2]=-1;
    rear++;
    while(front<rear){
        maintain(pq,rear,front);
        int weight=pq[front][0];
        int node=pq[front][1];
        int parent=pq[front][2];
        front++;
        if(vis[node]==1)
            continue;
        if(parent!=-1){
            arr[j][0]=parent;
            arr[j][1]=node;
            arr[j][2]=weight;
            j++;
        }
        vis[node]=1;
        for(int i=0; i<n; i++){
            if(mat[i][node]!=0 && !vis[i]){
                int adjacent=i;
                int edgeweight=mat[i][node];
                pq[rear][0]=edgeweight;
                pq[rear][1]=adjacent;
                pq[rear][2]=node;
                rear++;     
            }
        }
    }
    for(int i=0; i<j; i++){
        printf("%d %d (%d) ",arr[i][0],arr[i][1],arr[i][2]);
    }
    printf("\n");
    for(int i = 0; i < 100; i++){
        free(pq[i]);
    }
    free(pq);
    
    for(int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr);
}
void Weight(int** mat,int n,int x,int *sum){
    int vis[n];
    for(int i=0; i<n; i++)
        vis[i]=0;
    int **pq=(int**)malloc(100*sizeof(int*));
    for(int i=0; i<100; i++){
        pq[i]=(int*)malloc(3*sizeof(int));
    }
    int rear=0,front=0;
    pq[rear][0]=0;
    pq[rear][1]=x;
    pq[rear][2]=-1;
    rear++;
    while(front<rear){
        maintain(pq,rear,front);
        int weight=pq[front][0];
        int node=pq[front][1];
        int parent=pq[front][2];
        front++;
        if(vis[node]==1)
            continue;
        vis[node]=1;
        *sum=(*sum)+weight;
        for(int i=0; i<n; i++){
            if(mat[i][node]!=0 && !vis[i]){
                int adjacent=i;
                int edgeweight=mat[i][node];
                pq[rear][0]=edgeweight;
                pq[rear][1]=adjacent;
                pq[rear][2]=node;
                rear++;
            }
        }
    }
    for(int i = 0; i < 100; i++){
        free(pq[i]);
    }
    free(pq);
}
void TotalWeight(int** mat,int n){
    int sum=0;
    Weight(mat,n,0,&sum);
    printf("%d\n",sum);
}
int main(){
    int n,x;
    scanf("%d",&n);
    int **mat=(int**)malloc(n*sizeof(int*));
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
        scanf(" %c",&choice);
        switch(choice){
            case 's':scanf("%d",&x);
                    Sequence(mat,x,n);
                    break;
            case 'b':TotalWeight(mat,n);
                    break;
        }
    }while(choice!='e');
    for(int i = 0; i < n; i++){
        free(mat[i]);
    }
    free(mat);
    
    return 0;

}