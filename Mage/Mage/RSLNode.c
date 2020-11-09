#include"RSLNode.h"

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

int RSLNodeInsert(RSLNode* head, RSLDataType x, int index){
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

int RSLNodeDelete(RSLNode* head, int index, RSLDataType* x){
    RSLNode* p;
    RSLNode* d;
    p = head;
    if(index >= RSLNodeSize(head)){
        printf("delete error: invalid index!\n");
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
}       //����ѭ�����Է��������������
