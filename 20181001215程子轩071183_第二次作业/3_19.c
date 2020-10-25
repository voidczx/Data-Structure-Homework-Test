#include<stdlib.h>
#include<stdio.h>

#define MAXSIZE 10

typedef int DataType;
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
    if(theQueue->counter >= MAXSIZE){
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
        *x = theQueue->queueData[theQueue->head];
        theQueue->head = (theQueue->head + 1) % MAXSIZE;
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

void VisualNTSeqQueue(NTSeqQueue* theQueue){
    for(int i = 0; i < theQueue->counter; i++){
        int index = (theQueue->head + i) % MAXSIZE;
        printf("%d ", theQueue->queueData[index]);
    }
    printf("\n");
}

void main(){
    DataType quited;
    DataType getted;
    NTSeqQueue* myQueue = (NTSeqQueue*)malloc(sizeof(NTSeqQueue));
    for(int i = 0; i < 10; i++){
        NTSeqQueueEnter(myQueue, i+1);
    }
    VisualNTSeqQueue(myQueue);
    NTSeqQueueEnter(myQueue, 15);
    VisualNTSeqQueue(myQueue);
    NTSeqQueueQuit(myQueue, &quited);
    printf("the quited data is %d\n", quited);
    NTSeqQueueQuit(myQueue, &quited);
    printf("the quited data is %d\n", quited);
    VisualNTSeqQueue(myQueue);
    NTSeqQueueGet(myQueue, &getted);
    printf("the getted data is %d\n", getted);
}
