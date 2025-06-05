#include <stdio.h>
#include <stdlib.h>
int min(int a,int b){
    return a<b ? a: b;
}
int main(){
    int n;
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
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(mat[i][j]==-1)
                mat[i][j]=100000;
        }
    }
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(mat[i][j]==100000)
                mat[i][j]=-1;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}