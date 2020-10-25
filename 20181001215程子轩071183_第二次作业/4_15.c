#include<stdio.h>
#include<string.h>

int czxStrCmp(char* str01, char* str02){
    int size01 = strlen(str01);
    int size02 = strlen(str02);
    int size = (size01 > size02)? size02 : size01;
    for(int i = 0; i < size; i++){
        if(*(str01 + i) > *(str02 + i))
            return 1;
        if(*(str01 + i) < *(str02 + i))
            return -1;
    }
    if(size01 > size02)
        return 1;
    else if(size01 < size02)
        return -1;
    else
        return 0;
}

void main(){
    char str01[] = "blacknoir";
    char str02[] = "starlight";
    char str03[] = "thedeep";
    char str04[] = "homelander";
    printf("1 and 2: %d\n", czxStrCmp(str01, str02));
    printf("1 and 3: %d\n", czxStrCmp(str01, str03));
    printf("4 and 3: %d\n", czxStrCmp(str04, str03));
    printf("3 and 2: %d\n", czxStrCmp(str03, str02));
    printf("2 and 2: %d\n", czxStrCmp(str02, str02));
}
