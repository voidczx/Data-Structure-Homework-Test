#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}SLNode;

void SLNodeInitialize(SLNode**head){
    *head = (SLNode*) malloc(sizeof(SLNode));
    (*head)->next = NULL;
}

void VisualSLNode(SLNode* head){
    SLNode* t;
    t = head->next;
    while(t != NULL){
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");
}

int SLNodeInsert(SLNode*head, int x, int index){
    SLNode* t;
    t = head;
    for(int i = -1; i < index-1; i++){
        if(t->next == NULL){
            printf("insert error: invalid index\n");
            return 0;
        }
        t = t->next;
    }
    SLNode* n = (SLNode*)malloc(sizeof(SLNode));
    n->data = x;
    n->next = t->next;
    t->next = n;
    return 1;
}

void SLNodeInverse(SLNode* head){
    SLNode *current;
    SLNode *p;
    SLNode *q;
    SLNode *headCurrent;
    p = head->next;
    head->next = NULL;
    headCurrent = head;
    current = p;
    q = p;
    while(current->next != NULL){
        while(p->next != NULL){
            q = p;
            p = p->next;
        }
        headCurrent->next = p;
        headCurrent = p;
        q->next = NULL;
        p = current;
        q = p;
    }
    headCurrent->next = current;
}

void main(){
    SLNode* head;
    SLNodeInitialize(&head);
    for(int i = 0; i < 15; i++){
        SLNodeInsert(head, i, i);
    }
    VisualSLNode(head);
    SLNodeInverse(head);
    VisualSLNode(head);
}
