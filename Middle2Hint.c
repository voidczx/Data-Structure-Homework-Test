#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


/*************
    类型定义
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
    类型定义结束
******************/


/****************
    堆栈相关功能
*****************/

//堆栈初始化
void StackNodeInitialize(StackNode** head){
    *head = (StackNode*)malloc(sizeof(StackNode));
    (*head)->next = NULL;
}

//判断堆栈是否为空
int StackIsEmpty(const StackNode* head){
    if(head->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//堆栈置入
void StackNodePush(StackNode* head, DataType x){
    StackNode* n = (StackNode*)malloc(sizeof(StackNode));
    n->data = x;
    n->next = head->next;
    head->next = n;
}

//堆栈弹出
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

//取栈顶元素（但不弹出）
DataType StackNodeGet(StackNode* head){
    return head->next->data;
}

/*********************
    堆栈相关功能结束
**********************/

void DoubleStackNodeInitialize(DoubleStackNode** head){
    *head = (DoubleStackNode*)malloc(sizeof(DoubleStackNode));
    (*head)->next = NULL;
}

//判断堆栈是否为空
int DoubleStackIsEmpty(const DoubleStackNode* head){
    if(head->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//堆栈置入
void DoubleStackNodePush(DoubleStackNode* head, double x){
    DoubleStackNode* n = (DoubleStackNode*)malloc(sizeof(DoubleStackNode));
    n->data = x;
    n->next = head->next;
    head->next = n;
}

//堆栈弹出
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

//取栈顶元素（但不弹出）
double DoubleStackNodeGet(DoubleStackNode* head){
    return head->next->data;
}

/*******************
    单链表相关功能
********************/

//单链表初始化
void SLNodeInitialize(SLNode**head){
    *head = (SLNode*) malloc(sizeof(SLNode));
    (*head)->next = NULL;
}

//遍历输出单链表元素
void VisualSLNode(SLNode* head){
    SLNode* t;
    t = head->next;
    while(t != NULL){
        printf("%c", t->data);
        t = t->next;
    }
    printf("\n");
}

//单链表插入
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
    单链表相关功能结束
************************/

/********************
    顺序表相关功能
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
    顺序表相关功能结束
*************************/


/***************************
    中缀表达式转后缀表达式
****************************/


SLNode* Middle2Hint(DataType* middleExpression){
    SeqList* tempList;      //存储整合前的数
    SeqListInitialize(&tempList);
    int tempIndex = 0;
    StackNode* theStack;    //该指针所指向的堆栈用于暂存运算符
    SLNode* result;     //该指针所指向的单链表用于储存输出结果
    SLNodeInitialize(&result);
    StackNodeInitialize(&theStack);
    DataType* pointer;      //该指针用于控制输入串
    pointer = middleExpression;
    int index = 0;      //输出索引
    char getted;
    int continueFlag;   //该标志符用于判断指针在输入串的移动是否继续
    StackNodePush(theStack, '#');       //运算符堆栈加入#
    while(*pointer != '\0'){       //遍历输入串
        if(isdigit(*pointer)){
            SeqListInsert(tempList, (int)((*pointer)-'0'), tempIndex++);
            SLNodeInsert(result, *pointer, index++);
            continueFlag = 1;
        }       //当输入符为字母或数字时直接输出
        else if(*pointer == '.'){
            SLNodeInsert(result, *pointer, index++);
            continueFlag = 1;
        }
        else{   //当输入符为其他时进行运算符判断与处理
            //数的整合
            if(tempList->size != 0){
                SLNodeInsert(result, ' ', index++);
                SeqListClear(tempList);
                tempIndex = 0;
            }
            switch(*pointer){       //根据运算符优先表进行相应处理
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
    }       //如果输入串为空后运算符堆栈还有运算符则把运算符直接依序输出
    return result;
}

/*******************************
    中缀表达式转后缀表达式结束
********************************/


/*************************
    根据后缀表达式计算
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
     根据后缀表达式计算结束
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

