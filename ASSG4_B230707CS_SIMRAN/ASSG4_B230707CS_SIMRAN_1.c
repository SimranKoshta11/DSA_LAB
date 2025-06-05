#include <stdio.h>
#include <stdlib.h>
void heapify(int H[],int i,int n){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && H[left]>H[largest])
        largest=left;
    if(right<n && H[right]>H[largest])
        largest=right;
    if(largest!=i){
        int t=H[largest];
        H[largest]=H[i];
        H[i]=t;
        heapify(H,largest,n);
    }
}
void InsertKey(int H[],int key,int size){
    for(int i=0; i<size; i++){
        if(H[i]==key)
            return ;
    }
    H[size]=key;
    size++;
    for(int i=size/2-1; i>=0; i--){
        heapify(H,i,size);
    }
}
int FindMax(int H[],int count){
    if(count>0)
        return H[0];
    return -1;
}
void ExtractMax(int H[],int n){
    if(n==0){
        printf("-1\n");
        return;
    }
    int m=H[0];
    int t=H[n-1];
    H[n-1]=H[0];
    H[0]=t;
    n--;
    heapify(H,0,n);
    printf("%d ",m);
    for(int i=0; i<n; i++){
        printf("%d ",H[i]);
    }
    printf("\n");
}
void KthLargest(int H[],int k,int n){
    if(k>n-1){
        printf("-1\n");
        return ;
    }
    int arr[n];
    for(int i=0; i<n; i++){
        arr[i]=H[i];
    }
    for(int i=n-1; i>=k; i--){
        int s=arr[i];
        arr[i]=arr[0];
        arr[0]=s;
        heapify(arr,0,i);
    }
    printf("%d\n",arr[n-k]);
}
void DeleteKey(int H[],int x,int n){
    int find=0;
    for(int i=0; i<n; i++){
        if(H[i]==x){
            find=1;
            int s=H[i];
            H[i]=H[n-1];
            H[n-1]=s;
            n--;
            heapify(H,i,n);
            break;
        }
    }
    if(n==0){
        printf("0\n");
        return ;
    }
    if(find==0)
        printf("-1\n");
    else{
        for(int i=0; i<n; i++){
            printf("%d ",H[i]);
        }
        printf("\n");
    }
}
void ReplaceKey(int H[],int ok,int nk,int n){
    int find=0;
    for(int i=0; i<n; i++){
        if(H[i]==ok){
            find=1;
            if(nk<ok){
                H[i]=nk;
                heapify(H,i,n);
            }
            else{
                H[i]=nk;
                int j=i;
                while(j>0 && H[(j-1)/2]<H[j]){
                        int a=H[j];
                        H[j]=H[(j-1)/2];
                        H[(j-1)/2]=a;
                        j=(j-1)/2;
                }
            }
            break;
        }
    }
    if(find==0){
        if(ok-nk>0)
            printf("%d\n",ok-nk);
        else    
            printf("%d\n",nk-ok);
        return ;
    }
    for(int i=0; i<n; i++){
        printf("%d ",H[i]);
    }
    printf("\n");
}
int main(){
    int x,y,s;
    char ch;
    int H[100];
    int count=0;
    do{
        scanf("%c",&ch);
        switch(ch){
            case 'a':scanf("%d",&x);
                    InsertKey(H,x,count);
                    count++;
                    break;
            case 'b':s=FindMax(H,count);
                    printf("%d\n",s);
                    break;
            case 'c':ExtractMax(H,count);
                    count--;
                    break;
            case 'd':scanf("%d",&x);
                    KthLargest(H,x,count);
                    break;
            case 'e':scanf("%d",&x);
                    DeleteKey(H,x,count);
                    count--;
                    break;
            case 'f':scanf("%d %d",&x,&y);
                    ReplaceKey(H,x,y,count);
                    break;
        }
    }while(ch!='g');
}