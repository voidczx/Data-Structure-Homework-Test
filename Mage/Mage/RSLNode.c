#include"RSLNode.h"

void RSLNodeInitialize(RSLNode** head){
    *head = (RSLNode*) malloc(sizeof(RSLNode));        //先声明一块内存空间（头节点的实体）并用头指针指向
    (*head)->next = (*head);        //循环链表的特性：单链表指向NULL的地方都指向HEAD
}   //循环单链表初始化（这一步只生成了一个头节点）

int RSLNodeSize(RSLNode* head){
    RSLNode* p;
    p = head->next;
    int count = 0;
    while(p != head){
        count++;
        p = p->next;
    }
    return count;
}       //返回循环单链表内的节点数目（通过遍历循环单链表并计数的方式）

int RSLNodeInsert(RSLNode* head, RSLDataType x, int index){
    RSLNode* p;
    RSLNode* q;
    p = head;
    RSLNode* n = (RSLNode*)malloc(sizeof(RSLNode));
    n->data = x;
    if(index > RSLNodeSize(head)){
        printf("insert error: invalid index!\n");
        return 0;
    }       //首先判断要插入的位置是否合法（超过链表内节点数量即为非法）
    else{
        for(int i = -1; i < index-1; i++){
            p = p->next;
        }
        n->next = p->next;
        p->next = n;
        return 1;
    }
}       //循环单链表的插入功能（与单链表的插入功能类似）返回0为失败， 返回1为成功

int RSLNodeDelete(RSLNode* head, int index, RSLDataType* x){
    RSLNode* p;
    RSLNode* d;
    p = head;
    if(index >= RSLNodeSize(head)){
        printf("delete error: invalid index!\n");
        return 0;
    }       //也是首先判断要删除的节点是否存在
    else{
        for(int i = -1; i < index-1; i++){
            p = p->next;
        }
        d = p->next;
        *x = d->data;
        p->next = d->next;
        free(d);
        return 1;
    }
}       //循环单链表的删除功能 返回0为失败， 返回1为成功

int RSLNodeGet(RSLNode* head, int index, RSLDataType* output){
    RSLNode* p;
    p = head;
    if(index >= RSLNodeSize(head)){
        printf("error: invalid index!\n");
        return 0;
    }
    else{
        for(int i = -1; i < index-1; i++){
            p = p->next;
        }
        *output = p->next->data;
        return 1;
    }
}       //循环单链表的取数据功能，寻找相应节点的方式与删除功能相同，只不过最后一步从删除节点变为提取数据 返回0为失败， 返回1为成功 提取的数据储存在output参数中

void VisualRSLNode(RSLNode* head){
    RSLNode* p;
    p = head->next;
    while(p != head){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}       //遍历输出循环单链表中的数据

void VisualRSLNodeInverse(RSLNode* head){
    int size = RSLNodeSize(head);
    RSLNode* t;
    t = head;
    int i;
    for(int m=0;m<2;m++)
    {
      for(i = size; i > 0; i--){
        for(int j = 0; j < size; j++){
            t = t->next;
            }
            printf("%d ", t->data);

            }
        t = head;
        printf("\n");

    }
}       //利用循环特性反向遍历链表数据
