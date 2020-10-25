#include<stdio.h>

#define N 5

int GetAllElementSum(int(*theArray)[N]){
    int sum = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            sum += *(*(theArray+i)+j);
        }
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
    int theArray[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            theArray[i][j] = i + j + 1;
        }
    }
    VisualDim2Matrix(theArray);
    int sum = GetAllElementSum(theArray);
    printf("%d", sum);
}
