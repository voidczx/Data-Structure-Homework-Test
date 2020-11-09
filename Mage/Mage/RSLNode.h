#ifndef RSLNODE_H_INCLUDED
#define RSLNODE_H_INCLUDED

typedef int RSLDataType;   //���Ͷ��壬�����պ����ѭ���������ڵ���������

typedef struct node{
    RSLDataType data;
    struct node* next;
} RSLNode;  //���Ͷ���ѭ��������ڵ�

void RSLNodeInitialize(RSLNode** head);

int RSLNodeSize(RSLNode* head);

int RSLNodeInsert(RSLNode* head, RSLDataType x, int index);

int RSLNodeDelete(RSLNode* head, int index, RSLDataType* x);

int RSLNodeGet(RSLNode* head, int index, RSLDataType* output);

void VisualRSLNode(RSLNode* head);

void VisualRSLNodeInverse(RSLNode* head);

#endif // RSLNODE_H_INCLUDED
