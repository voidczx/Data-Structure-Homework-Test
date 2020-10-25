#include<stdio.h>
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
    p->next = head->next;
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

int IsPalindrome(char* charArray){
    int length = strlen(charArray);
    printf("size=%d\n", length);
    LSNode* forwardStack;
    LSNode* reverseStack;
    StackInitialize(&forwardStack);
    StackInitialize(&reverseStack);
    for(int i = 0; i < length; i++){
        StackPush(forwardStack, *(charArray+i));
    }
    for(int i = length-1; i >= 0; i--){
        StackPush(reverseStack, *(charArray+i));
    }
    int times = length / 2;
    char charA;
    char charB;
    for(int i = 0; i < times; i++){
        StackPop(forwardStack, &charA);
        StackPop(reverseStack, &charB);
        if(charA != charB){
            return 0;
        }
    }
    return 1;
}

void main(){
    char stringA[] = "ABCDEDCBA";
    char stringB[] = "ABCDEDBAC";
    printf("%s\n", stringA);
    printf("%d\n", IsPalindrome(stringA));
    printf("%s\n", stringB);
    printf("%d\n", IsPalindrome(stringB));
}
