#ifndef MERGINGSORT_H_INCLUDED
#define MERGINGSORT_H_INCLUDED

#include<stdlib.h>

typedef int MergingSortDataType;

MergingSortDataType* MergingForSort(MergingSortDataType* origin, int originSize, MergingSortDataType* result, int groupSize){
    result = (MergingSortDataType*)malloc(sizeof(MergingSortDataType)*originSize);
    int firstPointer, secondPointer, resultPointer, firstStart, firstEnd, secondStart, secondEnd;
    firstPointer = secondPointer = resultPointer = 0;
    firstStart = 0;
    firstEnd = firstStart + groupSize;
    secondStart = firstEnd;
    secondEnd = secondStart + groupSize;
    if(secondEnd >= originSize)
        secondEnd = originSize;
    while(resultPointer < originSize){
        for(firstPointer=firstStart, secondPointer=secondStart; firstPointer<firstEnd&&secondPointer<secondEnd;){
            MergingSortDataType firstValue, secondValue;
            firstValue = *(origin + firstPointer);
            secondValue = *(origin + secondPointer);
            if(firstValue <= secondValue){
                *(result + resultPointer) = firstValue;
                resultPointer++;
                firstPointer++;
            }
            if(firstValue > secondValue){
                *(result + resultPointer) = secondValue;
                resultPointer++;
                secondPointer++;
            }
        }
        while(firstPointer < firstEnd){
            *(result + resultPointer) = *(origin + firstPointer);
            resultPointer++;
            firstPointer++;
        }
        while(secondPointer < secondEnd){
            *(result + resultPointer) = *(origin + secondPointer);
            resultPointer++;
            secondPointer++;
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

MergingSortDataType* MergingSort(MergingSortDataType* origin, int originSize, MergingSortDataType* result){
    result = (MergingSortDataType*)malloc(sizeof(MergingSortDataType)*originSize);
    for(int i = 0; i < originSize; i++){
        *(result + i) = *(origin + i);
    }
    int groupSize = 1;
    int mergingTimes = originSize / 2;
    for(int i = 0; i < mergingTimes; i++){
        result = MergingForSort(result, originSize, result, groupSize);
        for(int j = 0; j < originSize; j++){
            printf("%d ", *(result + j));
        }
        printf("\n");
        groupSize = groupSize * 2;
    }
    return result;
}


#endif // MERGINGSORT_H_INCLUDED
