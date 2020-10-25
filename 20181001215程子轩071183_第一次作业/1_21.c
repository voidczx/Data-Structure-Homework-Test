#include<stdio.h>

#define N 5

int GetSumOfDiagnal(int(*theArray)[N]){
    int sum = 0;
    for(int i = 0; i < N; i++){
        sum += *(*(theArray+i)+i);
    }
    return sum;
}

void VisualDim2Matrix(int(*theArray)[N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d\t", *(*(theArray+i)+j));
        }
        printf("\n");
    }
}

void main(){
    int dim2Array[N][N] = {
                 {1, 2, 3, 4, 5},
                 {6, 7, 8, 9, 10},
                 {11, 12, 13, 14, 15},
                 {16, 17, 18, 19, 20},
                 {21, 22, 23, 24, 25}
                 };
    VisualDim2Matrix(dim2Array);
    int summary = GetSumOfDiagnal(dim2Array);
    printf("%d", summary);
}
