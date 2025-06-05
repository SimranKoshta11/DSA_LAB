#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void Build(char* pattern,int lps[],int m){
    int k=0;
    int i=1;
    while(i<m){
        if(pattern[i]==pattern[k]){
            k++;
            lps[i]=k;
            i++;
        }
        else{
            if(k!=0){
                k=lps[k-1];
            }
            else{
                lps[i]=0;
                i++;
            }
        }
    }
}
int main(){
    char* string=(char*)malloc(1000000*sizeof(char));
    char* pattern=(char*)malloc(100000*sizeof(char));
    scanf("%s",string);
    scanf("%s",pattern);
    int n=strlen(string);
    int m=strlen(pattern);
    if(m>n){
        printf("-1\n");
        return 0;
    }
    int lps[m];
    for(int i=0; i<m; i++)
        lps[i]=0;
    Build(pattern,lps,m);
    int i=0;
    int j=0,k,s=0;
    while(i<n){
        if(string[i]==pattern[j]){
            i++;
            j++;
            if(j==m){
                s++;
                k=i-j;
                j=lps[j-1];
            }
        }
        else{
            if(j!=0)
                j=lps[j-1];
            else
                i++;
        }
    }
    if(s==0)
        printf("-1\n");
    else
        printf("%d %d\n",k,s);
}