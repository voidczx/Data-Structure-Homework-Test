#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


/*************
    ���Ͷ���
**************/

typedef char DataType;

typedef struct Stack{
    DataType data;
    struct Stack* next;
} StackNode;

typedef struct DoubleStack{
    double data;
    struct DoubleStack* next;
} DoubleStackNode;

typedef struct Node{
    char data;
    struct Node* next;
}SLNode;

typedef struct{
    double data[20];
    int size;
}SeqList;

/*****************
    ���Ͷ������
******************/


/****************
    ��ջ��ع���
*****************/

//��ջ��ʼ��
void StackNodeInitialize(StackNode** head){
    *head = (StackNode*)malloc(sizeof(StackNode));
    (*head)->next = NULL;
}

//�ж϶�ջ�Ƿ�Ϊ��
int StackIsEmpty(const StackNode* head){
    if(head->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//��ջ����
void StackNodePush(StackNode* head, DataType x){
    StackNode* n = (StackNode*)malloc(sizeof(StackNode));
    n->data = x;
    n->next = head->next;
    head->next = n;
}

//��ջ����
int StackNodePop(StackNode* head, DataType* x){
    StackNode* p;
    if(StackIsEmpty(head)){
        printf("this is a empty stack!\n");
        return 0;
    }
    else{
        p = head->next;
        *x = p->data;
        head->next = p->next;
        free(p);
    }
}

//ȡջ��Ԫ�أ�����������
DataType StackNodeGet(StackNode* head){
    return head->next->data;
}

/*********************
    ��ջ��ع��ܽ���
**********************/

void DoubleStackNodeInitialize(DoubleStackNode** head){
    *head = (DoubleStackNode*)malloc(sizeof(DoubleStackNode));
    (*head)->next = NULL;
}

//�ж϶�ջ�Ƿ�Ϊ��
int DoubleStackIsEmpty(const DoubleStackNode* head){
    if(head->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//��ջ����
void DoubleStackNodePush(DoubleStackNode* head, double x){
    DoubleStackNode* n = (DoubleStackNode*)malloc(sizeof(DoubleStackNode));
    n->data = x;
    n->next = head->next;
    head->next = n;
}

//��ջ����
int DoubleStackNodePop(DoubleStackNode* head, double* x){
    DoubleStackNode* p;
    if(DoubleStackIsEmpty(head)){
        printf("this is a empty stack!\n");
        return 0;
    }
    else{
        p = head->next;
        *x = p->data;
        head->next = p->next;
        free(p);
    }
}

//ȡջ��Ԫ�أ�����������
double DoubleStackNodeGet(DoubleStackNode* head){
    return head->next->data;
}

/*******************
    ��������ع���
********************/

//�������ʼ��
void SLNodeInitialize(SLNode**head){
    *head = (SLNode*) malloc(sizeof(SLNode));
    (*head)->next = NULL;
}

//�������������Ԫ��
void VisualSLNode(SLNode* head){
    SLNode* t;
    t = head->next;
    while(t != NULL){
        printf("%c", t->data);
        t = t->next;
    }
    printf("\n");
}

//���������
int SLNodeInsert(SLNode*head, char x, int index){
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

/***********************
    ��������ع��ܽ���
************************/

/********************
    ˳�����ع���
*********************/

void SeqListInitialize(SeqList** seq){
    *seq = (SeqList*)malloc(sizeof(SeqList));
    (*seq)->size = 0;
}

int SeqListInsert(SeqList* seq, float x, int index){
    if(seq->size>=20){
        printf("Insert error: list has been full!");
        return 0;
    }
    else if(index >= 20){
        printf("Insert error: Invalid index!");
        return 0;
    }
    else{
        for(int i = (seq->size)-1; i >= index; i++){
            seq->data[i+1] = seq->data[i];
        }
        seq->data[index] = x;
        seq->size = seq->size+1;
        return 1;
    }
}

void SeqListClear(SeqList* seq){
    seq->size = 0;
}

/*************************
    ˳�����ع��ܽ���
*************************/


/***************************
    ��׺���ʽת��׺���ʽ
****************************/


SLNode* Middle2Hint(DataType* middleExpression){
    SeqList* tempList;      //�洢����ǰ����
    SeqListInitialize(&tempList);
    int tempIndex = 0;
    StackNode* theStack;    //��ָ����ָ��Ķ�ջ�����ݴ������
    SLNode* result;     //��ָ����ָ��ĵ��������ڴ���������
    SLNodeInitialize(&result);
    StackNodeInitialize(&theStack);
    DataType* pointer;      //��ָ�����ڿ������봮
    pointer = middleExpression;
    int index = 0;      //�������
    char getted;
    int continueFlag;   //�ñ�־�������ж�ָ�������봮���ƶ��Ƿ����
    StackNodePush(theStack, '#');       //�������ջ����#
    while(*pointer != '\0'){       //�������봮
        if(isdigit(*pointer)){
            SeqListInsert(tempList, (int)((*pointer)-'0'), tempIndex++);
            SLNodeInsert(result, *pointer, index++);
            continueFlag = 1;
        }       //�������Ϊ��ĸ������ʱֱ�����
        else if(*pointer == '.'){
            SLNodeInsert(result, *pointer, index++);
            continueFlag = 1;
        }
        else{   //�������Ϊ����ʱ����������ж��봦��
            //��������
            if(tempList->size != 0){
                SLNodeInsert(result, ' ', index++);
                SeqListClear(tempList);
                tempIndex = 0;
            }
            switch(*pointer){       //������������ȱ������Ӧ����
            case '+':
            case '-':
                if(StackNodeGet(theStack)!='(' && StackNodeGet(theStack)!='#'){
                    StackNodePop(theStack, &getted);
                    SLNodeInsert(result, getted, index++);
                    continueFlag = 0;
                }
                else{
                    StackNodePush(theStack, *pointer);
                    continueFlag = 1;
                }
                break;
            case '*':
            case '/':
                if(StackNodeGet(theStack)=='+' || StackNodeGet(theStack)=='-' || StackNodeGet(theStack)== '(' || StackNodeGet(theStack)=='#'){
                    StackNodePush(theStack, *pointer);
                    continueFlag = 1;
                }
                else{
                    StackNodePop(theStack, &getted);
                    SLNodeInsert(result, getted, index++);
                    continueFlag = 0;
                }
                break;
            case '(':
                StackNodePush(theStack, *pointer);
                continueFlag = 1;
                break;
            case ')':
                if(StackNodeGet(theStack)=='('){
                    StackNodePop(theStack, &getted);
                    continueFlag = 1;
                }
                else{
                    StackNodePop(theStack, &getted);
                    SLNodeInsert(result, getted, index++);
                    continueFlag = 0;
                }
                break;
            default:
                printf("error: unexpected char!");
                return NULL;
            }
        }
        if(continueFlag)
            pointer++;
    }
    if(tempList->size != 0){
        SLNodeInsert(result, ' ', index++);
        SeqListClear(tempList);
        tempIndex = 0;
    }
    while(StackNodeGet(theStack)!='#'){
        StackNodePop(theStack, &getted);
        SLNodeInsert(result, getted, index++);
    }       //������봮Ϊ�պ��������ջ�����������������ֱ���������
    return result;
}

/*******************************
    ��׺���ʽת��׺���ʽ����
********************************/


/*************************
    ���ݺ�׺���ʽ����
**************************/

double HintCalculate(SLNode* hintExpression){
    DoubleStackNode* numberStack;
    DoubleStackNodeInitialize(&numberStack);
    SLNode* p;
    SeqList* tempList;
    SeqListInitialize(&tempList);
    int tempIndex = 0;
    int dotIndex = -1;
    double result = 0.0;
    double number01;
    double number02;
    p = hintExpression->next;
    while(p != NULL){
        if(isdigit(p->data)){
            SeqListInsert(tempList, (int)((p->data)-'0'), tempIndex++);
        }
        else if(p->data == '.'){
            dotIndex = tempIndex;
        }
        else if((p->data) == ' '){
             if(tempList->size != 0){
                double number = 0;
                for(int i = 0; i < tempList->size; i++){
                    if(dotIndex < 0) dotIndex = tempList->size;
                    number +=(pow(10, dotIndex-1-i)) * (tempList->data[i]);
                }
                DoubleStackNodePush(numberStack, number);
                SeqListClear(tempList);
                tempIndex = 0;
                dotIndex = -1;
            }
        }
        else{
            switch(p->data){
            case '+':
                DoubleStackNodePop(numberStack, &number01);
                DoubleStackNodePop(numberStack, &number02);
                result = number01 + number02;
                DoubleStackNodePush(numberStack, result);
                break;
            case '-':
                DoubleStackNodePop(numberStack, &number01);
                DoubleStackNodePop(numberStack, &number02);
                result = number02 - number01;
                DoubleStackNodePush(numberStack, result);
                break;
            case '*':
                DoubleStackNodePop(numberStack, &number01);
                DoubleStackNodePop(numberStack, &number02);
                result = number01 * number02;
                DoubleStackNodePush(numberStack, result);
                break;
            case '/':
                DoubleStackNodePop(numberStack, &number01);
                DoubleStackNodePop(numberStack, &number02);
                result = number02 / number01;
                DoubleStackNodePush(numberStack, result);
                break;
            }
        }
        p = p->next;
    }
    result = DoubleStackNodeGet(numberStack);
    return result;
}

/****************************
     ���ݺ�׺���ʽ�������
****************************/


void main(){
    char theExpresstion[20];
    SLNode* head;
    printf("input the middle expression:\n");
    scanf("%s", theExpresstion);
    int i = 0;
    while(theExpresstion[i] != '\0'){
        printf("%c", theExpresstion[i]);
        i++;
    }
    printf("\n");
    head = Middle2Hint(theExpresstion);
    VisualSLNode(head);
    double result = HintCalculate(head);
    printf("\n%f\n",result);
}

