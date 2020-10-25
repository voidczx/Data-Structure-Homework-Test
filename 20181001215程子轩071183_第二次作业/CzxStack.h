#ifndef CZXSTACK_H_INCLUDED
#define CZXSTACK_H_INCLUDED

#include<string.h>
#include<stdlib.h>

typedef char DataType;

typedef struct stackNode{
    DataType data;
    struct stackNode* next;
}LSNode;

void StackInitialize(LSNode** head){
    (*head) = (LSNode*)malloc(sizeof(LSNode));
    (*head)->next = NULL;
}

int StackIsEmpty(LSNode* head){
    if(head->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int StackPush(LSNode* head, DataType x){
    LSNode* p = (LSNode*)malloc(sizeof(LSNode));
    p->data = x;
    p->next = head->next->next;
    head->next = p;
    return 1;
}

int StackPop(LSNode* head, DataType* x){
    if(StackIsEmpty(head) == 1){
        printf("Stack has already empty!\n");
        return 0;
    }
    else{
        LSNode* p;
        p = head->next;
        head->next = p->next;
        *x = p->data;
        free(p);
        return 1;
    }
}

int StackGet(LSNode* head, DataType* x){
    if(StackIsEmpty(head) == 1){
        printf("Stack has already empty!\n");
        return 0;
    }
    else{
        *x = head->next->data;
        return 1;
    }
}


#endif // CZXSTACK_H_INCLUDED
