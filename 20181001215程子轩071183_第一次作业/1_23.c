#include<stdio.h>

#define N 5

void VisualDim2Matrix(int(*theArray)[N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d\t", *(*(theArray+i)+j));
        }
        printf("\n");
    }
}

int GetSumOfSecondDiagnal(int(*theArray)[N]){
    int sum = 0;
    for(int i = 0; i < N; i++){
        sum += *(*(theArray+i)+(N-i-1));
    }
    return sum;
}

void main(){
    int theArray[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            theArray[i][j] = i + j + 1;
        }
    }
    VisualDim2Matrix(theArray);
    int sum = GetSumOfSecondDiagnal(theArray);
    printf("%d", sum);
}
