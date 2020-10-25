#include<stdio.h>
#include<stdlib.h>

#define N 20

typedef struct{
    int datas[20];
    int size;
} SeqList;

SeqList* InitialSeqList(){
    SeqList* seqList = (SeqList*) malloc(sizeof(SeqList));
    seqList->size = 0;
    return seqList;
}

int SeqListInsect(SeqList* seqList, int x, int index){
    if(seqList->size >= N){
        printf("insert error: the seqList has already full");
        return 0;
    }
    else{
        for(int i = seqList->size; i > index; i--){
            seqList->datas[i] = seqList->datas[i-1];
        }
        seqList->datas[index] = x;
        seqList->size = seqList->size + 1;
    }
}

int FindItsPosition(SeqList* seqList, int x){
    int order = 0;
    for(int i = 0; i < seqList->size; i++){
        if(x < seqList->datas[i]){
            order = i;
            break;
        }
    }
    if(SeqListInsect(seqList, x, order)){
        return 1;
    }
    else
        return 0;
}

void VisualSeqList(SeqList* seqList){
    for(int i = 0; i < seqList->size; i++){
        printf("%d ", seqList->datas[i]);
    }
}

void main(){
    SeqList* myList;
    myList = InitialSeqList();
    for(int i = 0; i < 10; i++){
        SeqListInsect(myList, i*2, i);
    }
    VisualSeqList(myList);
    printf("\n");
    FindItsPosition(myList, 13);
    VisualSeqList(myList);
}
