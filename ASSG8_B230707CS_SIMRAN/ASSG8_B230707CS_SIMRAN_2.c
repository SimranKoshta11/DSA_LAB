#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int bms(char* t,char* p){
    int n=strlen(t);
    int m=strlen(p);
    if(m==0 || n<m) return -1;
    int bad[256];
    for(int i=0; i<256; i++){
        bad[i]=-1;
    }
    for(int i=0; i<m; i++){ 
        bad[(int)p[i]]=i;
    }
    int s=0;
    while(s<=(n-m)){
        int j=m-1;
        while(j>=0 && p[j]==t[s+j])
            j--;
        if(j<0)
            return s;
        else{
            s+=(j-bad[(int)t[s+j]]>1) ? j-bad[(int)t[s+j]] : 1;
        }
    }
    return -1;
}

int main(){
    char *t=(char*)malloc(10000007*sizeof(char));
    char *p=(char*)malloc(100005*sizeof(char));
    if(fgets(t,10000007,stdin)==NULL || fgets(p,100005,stdin)==NULL){
        fprintf(stderr, "Error reading input\n");
        free(t);
        free(p);
        return 1;
    }
    t[strcspn(t, "\n")] = 0;
    p[strcspn(p, "\n")] = 0;
    int n=strlen(t);
    int m=strlen(p);
    int res = bms(t, p);
    printf("%d\n", res); 
    free(t);
    free(p);
    return 0;
}