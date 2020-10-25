#include<stdio.h>
#include<stdlib.h>

typedef int DataType;

typedef struct NoHeadSL{
    DataType data;
    struct NoHeadSL* next;
} NHSLNode;

void NHSLNodeInitialize(NHSLNode** head, DataType x){
    *head = (NHSLNode*)malloc(sizeof(NHSLNode));
    (*head)->data = x;
    (*head)->next = NULL;
}

int NHSLNodeInsert(NHSLNode** head, DataType x, int index){
    NHSLNode* p;
    NHSLNode* n = (NHSLNode*)malloc(sizeof(NHSLNode));
    p = *head;
    n->data = x;
    if(index == 0){
        n->next = p;
        *head = n;
        return 1;
    }
    else{
        for(int i = 0; i < index-1; i++){
            p = p->next;
            if(p==NULL){
                printf("insert error: invalid index\n");
                return 0;
            }
        }
        n->next = p->next;
        p->next = n;
        return 1;
    }
}

int NHSLNodeDelete(NHSLNode** head, int index, DataType* x){
    NHSLNode* p;
    NHSLNode* s;
    p = *head;
    if(index == 0){
        s = *head;
        *x = s->data;
        *head = (*head)->next;
        free(s);
        return 1;
    }
    for(int i = 0; i < index-1; i++){
        p = p->next;
        if(p == NULL){
            printf("delete error: invalid index\n");
            return 0;
        }
    }
    *x = p->next->data;
    s = p->next;
    p->next = s->next;
    free(s);
    return 1;
}

void VisualNHSLNode(NHSLNode* head){
    NHSLNode* p;
    p = head;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void main(){
    NHSLNode* head;
    NHSLNodeInitialize(&head, -1);
    VisualNHSLNode(head);
    int deleted;
    for(int i = 0; i < 15; i++){
        NHSLNodeInsert(&head, i, i);
    }
    VisualNHSLNode(head);
    NHSLNodeDelete(&head, 0, &deleted);
    VisualNHSLNode(head);
    NHSLNodeDelete(&head, 5, &deleted);
    VisualNHSLNode(head);
}
