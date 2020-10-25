#include<stdio.h>
#include<string.h>

void czxStrDelete(char* str, int index, int count){
    int originSize = strlen(str);
    char* newStr;
    if(index >= originSize){
        printf("Index Wrong!\n");
        return;
    }
    else if(index + count >= originSize){
        *(str + index) = '\0';
    }
    else{
        int newSize = originSize - count;
        int newIndex = index;
        newStr = (char*)malloc(sizeof(char)*newSize);
        for(int i = 0; i < index; i++){
            *(newStr + i) = *(str + i);
        }
        for(int i = index + count; i < originSize; i++){
            *(newStr + newIndex) = *(str + i);
            newIndex++;
        }
        strcpy(str, newStr);
        *(str + newIndex) = '\0';
    }
}

void main(){
    char str01[] = "A_train";
    printf("origin string = %s\n", str01);
    czxStrDelete(str01, 1, 4);
    printf("deleted string = %s\n", str01);
    char str02[] = "Butcher";
    printf("origin string02 = %s\n", str02);
    czxStrDelete(str02, 4, 4);
    printf("deleted string02 = %s\n", str02);
}
