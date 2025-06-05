#include <stdio.h>
#include <stdlib.h>
void initialize(int hash[],int n){
    for(int i=0; i<n; i++){
        hash[i]=-1;
    }
}
void LinearProbing(int hash[],int arr[],int n,int m){
    int res[m];
    int coll=0;
    int index,k,j;
    for(int i=0; i<m; i++){
        index=arr[i]%n;
        k=index;
        j=1;
        while(hash[index]!=-1){
            index=(k+j)%n;
            coll++;
            j++;
        }
        hash[index]=arr[i];
        res[i]=index;
    }
    for(int i=0; i<m; i++){
        printf("%d ",res[i]);
    }
    printf("\n%d\n",coll);
}
void QuadraticProbing(int hash[],int arr[],int n,int m){
    int res[m];
    int coll=0;
    int index,k;
    for(int i=0; i<m; i++){
        index=arr[i]%n;
        k=index;
        int j=1;
        while(hash[index]!=-1){
            index=(k+(j*j))%n;
            j++;
            coll++;
        }
        hash[index]=arr[i];
        res[i]=index;
    }
    for(int i=0; i<m; i++){
        printf("%d ",res[i]);
    }
    printf("\n%d\n",coll);
}
int LargePrime(int n){
    for (int i = n - 1; i > 1; i--) {
        int isPrime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) return i;
    }
    return 2;
}
void DoubleHashing(int hash[],int arr[],int n,int m){
    int res[m];
    int coll=0;
    int index,k;
    int R=LargePrime(n);
    for(int i=0; i<m; i++){
        int h1=arr[i]%n;
        int h2=R-(arr[i]%R);
        index=h1;
        int j=1;
        while(hash[index]!=-1){
            index = (h1 + j * h2) % n;
            j++;
            coll++;
        }
        hash[index]=arr[i];
        res[i]=index;
    }
    for(int i=0; i<m; i++){
        printf("%d ",res[i]);
    }
    printf("\n%d\n",coll);
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int hash[n];
    int arr[m];
    for(int i=0; i<m; i++)
        scanf("%d",&arr[i]);
    char choice;
    initialize(hash,n);
    do{
        scanf(" %c",&choice);
        switch(choice){
            case 'a': initialize(hash,n);
                    LinearProbing(hash,arr,n,m);
                    break;
            case 'b':initialize(hash,n);
                    QuadraticProbing(hash,arr,n,m);
                    break;
            case 'c':initialize(hash,n);
                    DoubleHashing(hash,arr,n,m);
                    break;
        }
    }while(choice!='d');
}