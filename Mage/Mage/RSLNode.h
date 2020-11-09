#ifndef RSLNODE_H_INCLUDED
#define RSLNODE_H_INCLUDED

typedef int RSLDataType;   //类型定义，方便日后更改循环单链表内的数据类型

typedef struct node{
    RSLDataType data;
    struct node* next;
} RSLNode;  //类型定义循环单链表节点

void RSLNodeInitialize(RSLNode** head);

int RSLNodeSize(RSLNode* head);

int RSLNodeInsert(RSLNode* head, RSLDataType x, int index);

int RSLNodeDelete(RSLNode* head, int index, RSLDataType* x);

int RSLNodeGet(RSLNode* head, int index, RSLDataType* output);

void VisualRSLNode(RSLNode* head);

void VisualRSLNodeInverse(RSLNode* head);

#endif // RSLNODE_H_INCLUDED
