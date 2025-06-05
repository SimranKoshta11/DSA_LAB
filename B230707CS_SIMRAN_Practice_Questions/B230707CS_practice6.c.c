#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;           
    struct Node* next;   
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1); 
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void Insertion(struct Node** head, int data) {    
    struct Node* newNode = createNode(data); 
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}
struct Node* reverseKGroup(struct Node* head, int k) {
    if (head == NULL || k == 1) return head;

    struct Node* dummy = createNode(0);
    dummy->next = head;
    
    struct Node* current = dummy, *next = dummy, *prev = dummy;
    int count = 0;
    while (current->next != NULL) {
        current = current->next;
        count++;
    }
    while (count >= k) {
        current = prev->next;
        next = current->next;

        for (int i = 1; i < k; i++) {
            current->next = next->next;
            next->next = prev->next;
            prev->next = next;
            next = current->next;
        }
        
        prev = current;
        count -= k;
    }

    struct Node* newHead = dummy->next;
    free(dummy);  
    return newHead;
}
void Display(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next; 
    }
}
int main() {
    struct Node* head = NULL;
    char ch;
    do{
        scanf(" %c",&ch);
    switch(ch){
        case 'a':{
            int num;
            scanf("%d",&num);
            Insertion(&head, num);
            break;
        }
        case 'c':{
        Display(head);
        break;
        }
        case 'd':
        exit;
    }        
    }while(ch != 'd');
    int k;
    scanf("%d",&k);
    head=reverseKGroup(head,k);
    Display(head);
    return 0;
}
