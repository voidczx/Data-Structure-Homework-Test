#include<stdio.h>
#include<stdlib.h>

typedef int DataType;   //���Ͷ��壬�����պ����ѭ���������ڵ���������

typedef struct node{
    DataType data;
    struct node* next;
} RSLNode;  //���Ͷ���ѭ��������ڵ�

void RSLNodeInitialize(RSLNode** head){
    *head = (RSLNode*) malloc(sizeof(RSLNode));        //������һ���ڴ�ռ䣨ͷ�ڵ��ʵ�壩����ͷָ��ָ��
    (*head)->next = (*head);        //ѭ����������ԣ�������ָ��NULL�ĵط���ָ��HEAD
}   //ѭ���������ʼ������һ��ֻ������һ��ͷ�ڵ㣩

int RSLNodeSize(RSLNode* head){
    RSLNode* p;
    p = head->next;
    int count = 0;
    while(p != head){
        count++;
        p = p->next;
    }
    return count;
}       //����ѭ���������ڵĽڵ���Ŀ��ͨ������ѭ�������������ķ�ʽ��

int RSLNodeInsert(RSLNode* head, DataType x, int index){
    RSLNode* p;
    RSLNode* q;
    p = head;
    RSLNode* n = (RSLNode*)malloc(sizeof(RSLNode));
    n->data = x;
    if(index > RSLNodeSize(head)){
        printf("insert error: invalid index!\n");
        return 0;
    }       //�����ж�Ҫ�����λ���Ƿ�Ϸ������������ڽڵ�������Ϊ�Ƿ���
    else{
        for(int i = -1; i < index-1; i++){
            p = p->next;
        }
        n->next = p->next;
        p->next = n;
        return 1;
    }
}       //ѭ��������Ĳ��빦�ܣ��뵥����Ĳ��빦�����ƣ�����0Ϊʧ�ܣ� ����1Ϊ�ɹ�

int RSLNodeDelete(RSLNode* head, int index, DataType* x){
    RSLNode* p;
    RSLNode* d;
    p = head;
    if(index >= RSLNodeSize(head)){
        printf("delete error: invalid index\n");
        return 0;
    }       //Ҳ�������ж�Ҫɾ���Ľڵ��Ƿ����
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
}       //ѭ���������ɾ������ ����0Ϊʧ�ܣ� ����1Ϊ�ɹ�

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
}       //ѭ���������ȡ���ݹ��ܣ�Ѱ����Ӧ�ڵ�ķ�ʽ��ɾ��������ͬ��ֻ�������һ����ɾ���ڵ��Ϊ��ȡ���� ����0Ϊʧ�ܣ� ����1Ϊ�ɹ� ��ȡ�����ݴ�����output������

void VisualRSLNode(RSLNode* head){
    RSLNode* p;
    p = head->next;
    while(p != head){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}       //�������ѭ���������е�����

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
}       //����ѭ�����Է��������������

void main(){
    //���������Դ���
    RSLNode* head;      //��������ͷָ��
    RSLNodeInitialize(&head);     //��ʼ��������ͷָ�뼴ָ����ͷ�ڵ�
    DataType geted;     //���ڴ洢ȡ���ݺ�����ȡ��������
    DataType deleted;       //���ڴ洢ɾ�������б�ɾ��������

    for(int i = 0; i < 18; i++){
        RSLNodeInsert(head, i*2, i);
    }       //��Ϊ��Ϊ�������18���ڵ㣬ÿ���ڵ�����������͵��������Ķ�����������ĸ��ڵ㣨����Ϊ3��������ֵ��Ϊ6��
    printf("the origin list:\n");
    VisualRSLNode(head);   //�����ʾ�����õ���������

    printf("size = %d\n", RSLNodeSize(head));   //�����ʾ�����ڽڵ���Ŀ

    RSLNodeInsert(head, 45, 20);
    RSLNodeDelete(head, 20, &deleted);      //�����ô�����������ò�����ɾ�����������Բ�����ɾ�������ļ����

    RSLNodeDelete(head, 15, &deleted);
    printf("the deleted list:\n");
    VisualRSLNode(head);
    printf("size = %d\n", RSLNodeSize(head));       //ɾ��������Ϊ15�Ľڵ㣬�������ʾɾ���������������ڵ���Ŀ

    RSLNodeGet(head, 12, &geted);
    printf("data[12] = %d\n", geted);       //ȡ����Ϊ12�Ľڵ�����ݣ�����ȡ���ݺ���

    printf("the reverse list:\n");
    VisualRSLNodeInverse(head);     //�������������ڵ�����
}
