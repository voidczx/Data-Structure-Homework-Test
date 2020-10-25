#include<stdio.h>
#include<stdlib.h>

typedef int DataType;   //类型定义，方便日后更改循环单链表内的数据类型

typedef struct node{
    DataType data;
    struct node* next;
} RSLNode;  //类型定义循环单链表节点

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

int RSLNodeInsert(RSLNode* head, DataType x, int index){
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

int RSLNodeDelete(RSLNode* head, int index, DataType* x){
    RSLNode* p;
    RSLNode* d;
    p = head;
    if(index >= RSLNodeSize(head)){
        printf("delete error: invalid index\n");
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

int RSLNodeGet(RSLNode* head, int index, DataType* output){
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
    for(int i = size; i > 0; i--){
        for(int j = 0; j < i; j++){
            t = t->next;
        }
        printf("%d ", t->data);
        t = head;
    }
    printf("\n");
}       //利用循环特性反向遍历链表数据

void main(){
    //主函数测试代码
    RSLNode* head;      //首先声明头指针
    RSLNodeInitialize(&head);     //初始化函数后头指针即指向了头节点
    DataType geted;     //用于存储取数据函数中取出的数据
    DataType deleted;       //用于存储删除函数中被删除的数据

    for(int i = 0; i < 18; i++){
        RSLNodeInsert(head, i*2, i);
    }       //人为地为链表插入18个节点，每个节点的数据是整型的其索引的二倍（例如第四个节点（索引为3）的数据值即为6）
    printf("the origin list:\n");
    VisualRSLNode(head);   //输出显示创建好的链表数据

    printf("size = %d\n", RSLNodeSize(head));   //输出显示链表内节点数目

    RSLNodeInsert(head, 45, 20);
    RSLNodeDelete(head, 20, &deleted);      //故意用错误的索引调用插入与删除函数，测试插入与删除函数的检错功能

    RSLNodeDelete(head, 15, &deleted);
    printf("the deleted list:\n");
    VisualRSLNode(head);
    printf("size = %d\n", RSLNodeSize(head));       //删除第索引为15的节点，并输出显示删除后的链表数据与节点数目

    RSLNodeGet(head, 12, &geted);
    printf("data[12] = %d\n", geted);       //取索引为12的节点的数据，测试取数据函数

    printf("the reverse list:\n");
    VisualRSLNodeInverse(head);     //反向遍历并输出节点数据
}
