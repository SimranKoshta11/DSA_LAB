#include<stdio.h>
#include<limits.h>
typedef struct stack
{
    int A[20];
    int top;
}Stack;
void push(Stack* s,int a)
{
s->A[++s->top]=a;

}
int pop(Stack* s)
{
    int c=s->A[s->top--];
    return c;
}
int * NGE(int A[],int n)
{
    int max=INT_MIN;
    for(int i=0;i<n;i++)
    {
        if(max<A[i])
        max=A[i];
    }
    int B[max+1],S[n];
    for(int i=0;i<max+1;i++)
    {
        B[i]=0;
    }
    for(int i=0;i<n;i++)
    {
        B[A[i]]++;
    }
    Stack s;
    s.top=-1;
    push(&s,0);
    int c=0;
    for(int i=1;i<n;i++){
        do{
            c=0;
            if(s.top==-1)
            {
                push(&s,i);c=1;
            }
        else if(B[A[s.A[s.top]]]>=B[A[i]])
        {
            push(&s,i);
            c=1;
        }
        else{
          int c=pop(&s);
          S[c]=A[i];
        }
        }while(c!=1);
    }while(s.top!=-1)
    {
        S[pop(&s)]=-1;
    }
    for(int i=0;i<n;i++)
    printf("%d ",S[i]);
}
int main()
{
    Stack s;
    s.top=-1;
    int n ;
    scanf("%d",&n);
    int A[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&A[i]);
    }
    NGE(A,n);
}