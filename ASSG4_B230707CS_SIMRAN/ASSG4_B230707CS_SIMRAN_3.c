#include <stdio.h>
#include <stdlib.h>
struct Node{
    int job_id;
    int priority;
};
typedef struct Node* node;
void swap(node *a,node *b){
    node tmp=*a;
    *a=*b;
    *b=tmp;
}
void heapify(node que[],int i,int n){
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && que[left]->priority<que[smallest]->priority)
        smallest=left;
    if(right<n && que[right]->priority<que[smallest]->priority)
        smallest=right;
    if(smallest!=i){
        swap(&que[smallest],&que[i]);
        heapify(que,smallest,n);
    }
}
void Add(node que[],int a,int b,int size){
    for(int i=0; i<size; i++){
        if(que[i]->priority==b)
            return;
    }
    que[size]->job_id=a;
    que[size]->priority=b;
    size++;
    for(int i=size/2-1; i>=0; i--){
        heapify(que,i,size);
    }
}
void Schedule(node que[],int count){
    if(count==0)
        printf("-1\n");
    else{
        printf("%d\n",que[0]->job_id);
        swap(&que[0],&que[count-1]);
        count--;
        heapify(que,0,count);
    }
}
void Next_job(node que[],int n){
    if(n==0){
        printf("-1\n");
        return ;
    }
    printf("%d\n",que[0]->job_id);
}
void Replace_priority(node que[],int a,int b,int n){
    int find=0;
    for(int i=0; i<n; i++){
        if(que[i]->job_id==a){
            find=1;
            que[i]->priority=b;
            if(b>que[i]->priority){
                heapify(que,i,n);
            }
            else{
                int j=i;
                while(j>0 && que[j]->priority<que[(j-1)/2]->priority){
                    swap(&que[j],&que[(j-1)/2]);
                    j=(j-1)/2;
                }
            }
            break;
        }
    }
    if(find==0)
        printf("-1\n");
}
void Display(node que[],int n){
    if(n==0)
        printf("-1\n");
    else{
        for(int i=0; i<n; i++){
            printf("%d %d\n",que[i]->job_id,que[i]->priority);
        }
    }
}
int main(){
    int w,x,count=0;
    char ch;
    node que[100];
    for(int i=0; i<100; i++){
        que[i]=(node)malloc(sizeof(struct Node));
    }
    do{
        scanf("%c",&ch);
        switch(ch){
            case 'a':scanf("%d %d",&w,&x);
                    Add(que,w,x,count);
                    count++;
                    break;
            case 'b':Schedule(que,count);
                    count--;
                    break;
            case 'c':Next_job(que,count);
                    break;
            case 'd':scanf("%d %d",&w,&x);
                    Replace_priority(que,w,x,count);
                    break;
            case 'e':Display(que,count);
                    break;
        }
    }while(ch!='g');
}