#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Node{
    char name[30];
    char rollno[30];
    int age;
    struct Node* next;
};
typedef struct Node* node;
node create(char name[],char rollno[],int age){
    node temp=(node)malloc(sizeof(struct Node));
    strcpy(temp->name,name);
    strcpy(temp->rollno,rollno);
    temp->age=age;
    temp->next=NULL;
    return temp;
}
int index1(char name[],int age){
    int sum=0;
    for(int i=0; name[i]!='\0'; i++){
        sum=sum+name[i];
    }
    sum=sum+age;
    return sum%4;
}
void insert(node hash[],char name[],char rollno[],int age){
    node temp=create(name,rollno,age);
    int i=index1(name,age);
    temp->next=hash[i];
    hash[i]=temp;
}
void GroupIndexAndSplit(char name[],node hash[]){
    int find=0;
    for(int i=0; i<4; i++){
        node curr=hash[i];
        while(curr!=NULL){
            if(strcmp(curr->name,name)==0){
                int j=index1(curr->name,curr->age);
                printf("%d\n",j);
                find=1;
                break;
            }
            curr=curr->next;
        }
        if(find) break;
    }
}

void Group_CountAndList(node hash[],int k){
    node curr=hash[k];
    int count=0;
    while(curr!=NULL){
        count++;
        curr=curr->next;
    }
    if(count!=0)
        printf("%d ",count);
    else{
        printf("0\n");
        return;
    }
    /*curr=hash[k];
    node index=NULL;
    while(curr!=NULL){
        index=curr->next;
        while(index!=NULL){
            if(strcmp(curr->name,index->name)>0){
                char t[30],s[30];
                int a;
                strcpy(t,curr->name);
                strcpy(curr->name,index->name);
                strcpy(index->name,t);
                strcpy(s,curr->rollno);
                strcpy(curr->rollno,index->rollno);
                strcpy(index->rollno,s);
                a=curr->age;
                curr->age=index->age;
                index->age=a;
            }
            index=index->next;
        }
        curr=curr->next;
    }
    curr=hash[k];
    for(int i=0; i<count; i++){
        printf("%s ",curr->name);
        curr=curr->next;
    }
    printf("\n");*/

    char str[count][30];
    curr=hash[k];
    for(int i=0; i<count; i++){
        strcpy(str[i],curr->name);
        curr=curr->next;
    }
    char t[30];
    for(int i=0; i<count; i++){
        for(int j=0; j<count-1-i; j++){
            if(strcmp(str[j],str[j+1])>0){
                    strcpy(t,str[j]);
                    strcpy(str[j],str[j+1]);
                    strcpy(str[j+1],t);
            }
        }
    }
    for(int i=0; i<count; i++){
        printf("%s ",str[i]);
    }
    printf("\n");
}
void Group_ListByBranch(node hash[],int k,char branch[]){
    node curr=hash[k];
    int find=0;
    for(int i=0; i<2; i++){
        branch[i]=toupper(branch[i]);
    }
    branch[2]='\0';
    while(curr!=NULL){
        int len=strlen(curr->rollno);
        if(curr->rollno[len-2]==branch[0] && curr->rollno[len-1]==branch[1]){
            printf("%s ",curr->name);
            find=1;
        }
        curr=curr->next;
    }
    if(!find)
        printf("-1\n");
    else
        printf("\n");
}
node search(node hash[],char rollno[]){
    int find=0;
    for(int i=0; i<4; i++){
        node curr=hash[i];
        while(curr!=NULL){
            if(strcmp(rollno,curr->rollno)==0){
                return curr;
            }
            curr=curr->next;
        }
    }
    return NULL;
}
void StudentDetails(node st,char rollno[]){
    if(st!=NULL){
        int len=strlen(st->rollno);
        printf("%s %d %c%c\n",st->name,st->age,st->rollno[len-2],st->rollno[len-1]);
    }
    else 
        printf("-1\n");
}
void Group_TransferAllByBranch(node hash[],int a,int b,char branch[]){
    int c=0;
    node curr=hash[a];
    node prev=NULL;
    for(int i=0; i<2; i++){
        branch[i]=toupper(branch[i]);
    }
    branch[2]='\0';
    while(curr!=NULL){
        int len=strlen(curr->rollno);
        if(curr->rollno[len-2]==branch[0] && curr->rollno[len-1]==branch[1]){
            if(prev==NULL){
                hash[a]=curr->next;
            }
            else{
                prev->next=curr->next;
            }
            node temp=curr;
            temp->next=hash[b];
            hash[b]=temp;
            c++;
            curr=curr->next;
        }
        else{
            prev=curr;
            curr=curr->next;
        }
    }
    printf("%d\n",c);
}
int main(){
    char choice;
    int n,k,age,a,b;
    node hash[4]={NULL,NULL,NULL,NULL};
    char name[30],branch[3];
    char rollno[30];
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%s %s %d",name,rollno,&age);
        insert(hash,name,rollno,age);
    }
    do{
        scanf(" %c",&choice);
        switch(choice){
            case 'a': scanf("%s",name);
                    GroupIndexAndSplit(name,hash);
                    break;
            case 'b':scanf("%d",&k);
                    Group_CountAndList(hash,k);
                    break;
            case 'c':scanf("%d %s",&k,branch);
                    Group_ListByBranch(hash,k,branch);
                    break;
            case 'd':scanf("%s",rollno);
                    node st=search(hash,rollno);
                    StudentDetails(st,rollno);
                    break;
            case 'e':scanf("%d %d %s",&a,&b,branch);
                    Group_TransferAllByBranch(hash,a,b,branch);
                    break;
        }
    }while(choice!='f');
}