#ifndef NOTAILSEQQUEUE_H_INCLUDED
#define NOTAILSEQQUEUE_H_INCLUDED

#include<stdlib.h>
#include<stdio.h>

#define MAXSIZE 50

typedef BinaryTreeNode DataType;
typedef struct queueNode{
    DataType queueData[MAXSIZE];
    int head;
    int counter;
} NTSeqQueue;

void NTSeqQueueInitialize(NTSeqQueue* theQueue){
    theQueue->head = 0;
    theQueue->counter = 0;
}

int NTSeqQueueEnter(NTSeqQueue* theQueue, DataType x){
    if(theQueue->counter > MAXSIZE){
        printf("Queue is full!\n");
        return 0;
    }
    else
    {
        int index = (theQueue->head + theQueue->counter) % MAXSIZE;
        theQueue->queueData[index] = x;
        theQueue->counter++;
        return 1;
    }
}

int NTSeqQueueIsEmpty(NTSeqQueue* theQueue){
    if(theQueue->counter == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int NTSeqQueueQuit(NTSeqQueue* theQueue, DataType* x){
    if(NTSeqQueueIsEmpty(theQueue) == 1){
        printf("The Queue Is Empty!\n");
        return 0;
    }
    else{
        theQueue->queueData[head] = *x;
        theQueue->head++;
        theQueue->counter--;
        return 0;
    }
}

int NTSeqQueueGet(NTSeqQueue* theQueue, DataType* x){
    if(NTSeqQueueIsEmpty(theQueue) == 1){
        printf("The Queue Is Empty!\n");
        return 0;
    }
    else{
        *x = theQueue->queueData[theQueue->head];
        return 1;
    }
}

#endif // NOTAILSEQQUEUE_H_INCLUDED
