#include<stdio.h>
#include<stdlib.h>


int* GetBiggestAndSecondBiggestInt(int number01, int number02, int number03){
    int numbers[3] = {number01, number02, number03};
    int temp;
    for(int i = 0; i < 3; i++){
        for(int j = i; j < 2; j++){
            if(numbers[j+1] > numbers[j]){
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }
    //static int results[2];
    int* results = (int*) malloc(sizeof(int[2]));
    results[0] = numbers[0];
    results[1] = numbers[1];
    return results;
    printf("biggest: %d, second biggest: %d", numbers[0], numbers[1]);
}

void main(){
    printf("please input three integers which separate by space\n");
    int num01, num02, num03;
    scanf("%d %d %d", &num01, &num02, &num03);
    int* result = GetBiggestAndSecondBiggestInt(num01, num02, num03);
    for(int i = 0; i < 2; i++){
        printf("%d ", *(result+i));
    }
}
