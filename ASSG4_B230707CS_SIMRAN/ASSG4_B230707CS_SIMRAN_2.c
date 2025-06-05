#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Node{
    int patient_id;
    char name[50];
    int serverity;
};
typedef struct Node* node;
void swap(node *a,node *b){
    node tmp=*a;
    *a=*b;
    *b=tmp;
}
void heapify(node arr[],int i,int n){
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && arr[left]->serverity<arr[smallest]->serverity)
        smallest=left;
    if(right<n && arr[right]->serverity<arr[smallest]->serverity)
        smallest=right;
    if(smallest!=i){
        swap(&arr[smallest],&arr[i]);
        heapify(arr,smallest,n);
    }
}
void AdmitPatient(node pq[],int pi,char name[],int ser,int size){
    for(int i=0; i<size; i++){
        if(pq[i]->serverity==ser)
            return ;
    }
    pq[size]->patient_id=pi;
    strcpy(pq[size]->name,name);
    pq[size]->serverity=ser;
    size++;
    for(int i=size/2-1; i>=0; i--){
        heapify(pq,i,size);
    }
    for(int i=0; i<size; i++){
        printf("%d ",pq[i]->patient_id);
    }
    printf("\n");
}
void TreatPatient(node pq[],int n){
    if(n==0){
        printf("-1\n");
        return ;
    }
    char n1[50];
    strcpy(n1,pq[0]->name);
    for(int i=0; n1[i]!='\0';i++){
        n1[i]=tolower(n1[i]);
    }
    printf("%d %s\n",pq[0]->patient_id,n1);
    swap(&pq[0],&pq[n-1]);
    n--;
    heapify(pq,0,n);
}
void UpdateServerity(node pq[],int pi,int ns,int n){
    int find=0;
    for(int i=0; i<n; i++){
        if(pq[i]->patient_id==pi){
            find=1;
            if(ns>pq[i]->serverity){
                pq[i]->serverity=ns;
                heapify(pq,i,n);
            }
            else{
                pq[i]->serverity=ns;
                int j=i;
                while(j>0 && pq[j]->serverity<pq[(j-1)/2]->serverity){
                    swap(&pq[j],&pq[(j-1)/2]);
                    j=(j-1)/2;
                }
            }
            break;
        }
    }
    if(find==0){
        printf("-1\n");
        return ;
    }
    for(int i=0; i<n; i++){
        printf("%d ",pq[i]->patient_id);
    }
    printf("\n");
}
void QueryPatient(node pq[],int pi,int n){
    int find=0;
    for(int i=0; i<n; i++){
        if(pq[i]->patient_id==pi){
            find=1;
            char n1[50];
            strcpy(n1,pq[i]->name);
            for(int i=0; n1[i]!='\0';i++){
                n1[i]=tolower(n1[i]);
            }
            printf("%s %d\n",n1,pq[i]->serverity);
            break;
        }
    }
    if(find==0){
        printf("-1\n");
        return ;
    }
}
void FindMostSevere(node pq[],int n){
    if(n==0)
        printf("-1\n");
    if(n<=2){
        node arr[n];
        for(int i=0; i<n; i++){
            arr[i]=pq[i];
        }
        for(int i=n-1; i>=0; i--){
            swap(&arr[i],&arr[0]);
            printf("%d %s %d\n",arr[i]->patient_id,arr[i]->name,arr[i]->serverity);
            heapify(arr,0,i);
        }
    }
    else{
        node arr[n];
        for(int i=0; i<n; i++){
            arr[i]=pq[i];
        }
        for(int i=n-1; i>=n-3; i--){
            swap(&arr[i],&arr[0]);
            printf("%d %s %d\n",arr[i]->patient_id,arr[i]->name,arr[i]->serverity);
            heapify(arr,0,i);
        }
        
    }
}
int main(){
    node pq[100];
    for (int i = 0; i < 100; i++) {
        pq[i] = (node)malloc(sizeof(struct Node));  
    }
    char ch;
    int a1,b1,count=0;
    char n[50];
    do{
        scanf("%c",&ch);
        switch(ch){
            case 'a':scanf("%d %d %s",&a1,&b1,n);
                    AdmitPatient(pq,a1,n,b1,count);
                    count++;
                    break;
            case 'b':TreatPatient(pq,count);
                    count--;
                    break;
            case 'c':scanf("%d %d",&a1,&b1);
                    UpdateServerity(pq,a1,b1,count);
                    break;
            case 'd':scanf("%d",&a1);
                    QueryPatient(pq,a1,count);
                    break;
            case 'e':FindMostSevere(pq,count);
                    break;
        }
    }while(ch!='g');
}