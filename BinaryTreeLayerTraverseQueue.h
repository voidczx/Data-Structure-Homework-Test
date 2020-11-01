#ifndef BINARYTREELAYERTRAVERSEQUEUE_H_INCLUDED
#define BINARYTREELAYERTRAVERSEQUEUE_H_INCLUDED

#ifndef NOTAILSEQQUEUE_H_INCLUDED
#define NOTAILSEQQUEUE_H_INCLUDED

#include<stdlib.h>
#include<stdio.h>

#define MAXSIZE 50

typedef BinaryTreeNode QueueDataType;
typedef struct queueNode{
    QueueDataType queueData[MAXSIZE];
    int head;
    int counter;
} NTSeqQueue;

void NTSeqQueueInitialize(NTSeqQueue* theQueue){
    theQueue->head = 0;
    theQueue->counter = 0;
}

int NTSeqQueueEnter(NTSeqQueue* theQueue, QueueDataType x){
    if(theQueue->counter > MAXSIZE){
        printf("Queue is full!\n");
        return 0;
    }
    else
    {
        int index = (theQueue->head + theQueue->counter) % MAXSIZE;
        theQueue->queueData[index] = x;
        theQueue->counter++;
        //printf("ENTER:%c\n", theQueue->queueData[index].data);
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

int NTSeqQueueQuit(NTSeqQueue* theQueue, QueueDataType* x){
    if(NTSeqQueueIsEmpty(theQueue) == 1){
        printf("The Queue Is Empty!\n");
        return 0;
    }
    else{
        *x = theQueue->queueData[theQueue->head];
        theQueue->head = (theQueue->head + 1) % MAXSIZE;
        theQueue->counter--;
        return 1;
    }
}

int NTSeqQueueGet(NTSeqQueue* theQueue, QueueDataType* x){
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

#endif // BINARYTREELAYERTRAVERSEQUEUE_H_INCLUDED
