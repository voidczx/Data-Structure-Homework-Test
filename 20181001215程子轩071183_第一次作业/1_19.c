#include<stdio.h>

int FindBiggerInt(int num01, int num02){
    return (num01 > num02)? num01 : num02;
}

void main(){
    int number01, number02;
    printf("Input two integer which separate by space\n");
    scanf("%d %d", &number01, &number02);
    printf("%d", FindBiggerInt(number01, number02));
}
