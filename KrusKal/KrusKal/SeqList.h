#ifndef SEQLIST_H_INCLUDED
#define SEQLIST_H_INCLUDED
#include <stdlib.h>

#define SeqMax 5

typedef char SeqListDataType;

typedef struct{
    SeqListDataType* data;
    int theSize;
    int maxSize;
} SeqList;

void SeqListInitialize(SeqList* seqList){
    seqList->data = (SeqListDataType*)malloc(sizeof(SeqListDataType) * SeqMax);
    seqList->theSize = 0;
    seqList->maxSize = SeqMax;
}

void SeqListAppend(SeqList* seqList, SeqListDataType x){
    if(seqList->theSize >= seqList->maxSize){
        SeqListDataType* newData;
        newData = (SeqListDataType*)malloc(sizeof(SeqListDataType)*(seqList->maxSize + SeqMax));
        seqList->maxSize = seqList->maxSize + SeqMax;
        for(int i = 0; i < seqList->theSize; i++){
            *(newData + i) = *(seqList->data + i);
        }
        free(seqList->data);
        seqList->data = newData;
    }
    *(seqList->data + seqList->theSize) = x;
    seqList->theSize++;
}

#endif // SEQLIST_H_INCLUDED
