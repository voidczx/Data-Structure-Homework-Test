#ifndef KRUSTAL_H_INCLUDED
#define KRUSTAL_H_INCLUDED

#include <stdlib.h>

typedef int WeightType;

typedef struct{
    WeightType weight;
    int startPoint;
    int overPoint;
} KrustalWeight;


KrustalWeight* KrustalMergingForSort(KrustalWeight* origin, int originSize, KrustalWeight* result, int groupSize){
    result = (KrustalWeight*)malloc(sizeof(KrustalWeight) * originSize);
    int firstPointer, secondPointer, resultPointer, firstStart, firstEnd, secondStart, secondEnd;
    firstPointer = secondPointer = resultPointer = 0;
    firstStart = 0;
    firstEnd = firstStart + groupSize;
    if(firstEnd >= originSize)
        firstEnd = originSize - 1;
    secondStart = firstEnd;
    secondEnd = secondStart + groupSize;
    if(secondEnd >= originSize)
        secondEnd = originSize;
    while(resultPointer < originSize){
        for(firstPointer=firstStart, secondPointer=secondStart; firstPointer<firstEnd&&secondPointer<secondEnd;){
            KrustalWeight firstValue, secondValue;
            firstValue = *(origin + firstPointer);
            secondValue = *(origin + secondPointer);
            if(firstValue.weight <= secondValue.weight){
                *(result + resultPointer) = firstValue;
                resultPointer++;
                firstPointer++;
            }
            if(firstValue.weight > secondValue.weight){
                *(result + resultPointer) = secondValue;
                resultPointer++;
                secondPointer++;
            }
        }
        while(firstPointer < firstEnd){
            *(result + resultPointer) = *(origin + firstPointer);
            firstPointer++;
            resultPointer++;
        }
        while(secondPointer < secondEnd){
            *(result + resultPointer) = *(origin + secondPointer);
            secondPointer++;
            resultPointer++;
        }
        firstStart = secondEnd;
        firstEnd = firstStart + groupSize;
        if(firstEnd >= originSize)
            firstEnd = originSize - 1;
        secondStart = firstEnd;
        secondEnd = secondStart + groupSize;
        if(secondEnd >= originSize)
            secondEnd = originSize;
    }
    return result;
}

KrustalWeight* KrustalMergingSort(KrustalWeight* origin, int originSize){
//    KrustalWeight* result;
//    result = (KrustalWeight*)malloc(sizeof(KrustalWeight) * originSize);
//    for(int i = 0; i < originSize; i++){
//        *(result + i) = *(origin + i);
//    }
    KrustalWeight* result;
    int groupSize = 1;
    int mergingTimes = originSize / 2;
    for(int i = 0; i < mergingTimes; i++){
        result = KrustalMergingForSort(origin, originSize, origin, groupSize);
        free(origin);
        origin = result;

//        for(int i = 0; i < originSize; i++){
//        printf("%d %d %d\n", origin[i].weight, origin[i].startPoint, origin[i].overPoint);
//    }
//    printf("\n");

        groupSize = groupSize * 2;
    }
    return origin;
}

KrustalWeight* GetWeightArray(Graph* theGraph){
    int arraySize = theGraph->lineSize;
    int pointNumber = theGraph->point.theSize;
    KrustalWeight* weightArray;
    weightArray = (KrustalWeight*)malloc(sizeof(KrustalWeight) * arraySize);
    int arrayIndex = 0;
    for(int i = 0; i < pointNumber; i++){
        for(int j = 0; j < i + 1; j++){
            if(theGraph->lines[i][j] < Infinite){
                weightArray[arrayIndex].weight = theGraph->lines[i][j];
                weightArray[arrayIndex].startPoint = i;
                weightArray[arrayIndex].overPoint = j;
                arrayIndex++;
            }
        }
    }
    return weightArray;
}

KrustalWeight* KrustalGenerate(Graph* theGraph){
    KrustalWeight* weightArray;
    KrustalWeight* sortArray;
    KrustalWeight* resultArray;
    int* connection = (int*)malloc(sizeof(int)*theGraph->point.theSize);
    int allocationNumber = 0;
    for(int i = 0; i < theGraph->point.theSize; i++){
        *(connection + i) = allocationNumber;
    }
    allocationNumber++;
    weightArray = GetWeightArray(theGraph);
    sortArray = KrustalMergingSort(weightArray, theGraph->lineSize);
//    for(int i = 0; i < theGraph->lineSize; i++){
//        printf("%d %c %c\n", sortArray[i].weight, *((theGraph->point).data + sortArray[i].startPoint), *((theGraph->point).data + sortArray[i].overPoint));
//    }
    resultArray = (KrustalWeight*)malloc(sizeof(KrustalWeight)*(theGraph->point.theSize-1));
    int resultIndex = 0;
    for(int i = 0; i < theGraph->lineSize; i++){
        KrustalWeight currentWeight = *(sortArray + i);
        int startFlag = *(connection + currentWeight.startPoint);
        int overFlag = *(connection + currentWeight.overPoint);
        if(startFlag != overFlag || (startFlag == 0 && overFlag == 0)){
            *(resultArray + i) = currentWeight;
            if(startFlag == 0 && overFlag == 0){
                *(connection + currentWeight.startPoint) = allocationNumber;
                *(connection + currentWeight.overPoint) = allocationNumber;
                allocationNumber++;
            }
            else if(overFlag == 0 || startFlag == 0){
                *(connection + currentWeight.overPoint) = *(connection + currentWeight.startPoint) = startFlag + overFlag;
            }
            else{
                for(int j = 0; j < theGraph->point.theSize; j++){
                    if((*(connection + j)) == (*(connection + currentWeight.overPoint)))
                        *(connection + j) = *(connection + currentWeight.startPoint);
                }
            }
            resultIndex++;
        }
    }
    return resultArray;
}


#endif // KRUSTAL_H_INCLUDED
