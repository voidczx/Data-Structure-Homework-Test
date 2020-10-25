#include<stdio.h>
#include<malloc.h>

#define Max 256
#define Zero 0

typedef int DataType;

typedef struct{
    DataType data;
    int rowIndex;
    int colIndex;
}MatrixElement;

typedef struct{
    MatrixElement matrix[Max];
    int rowNumber;
    int colNumber;
    int totalNumber;
}CompressMatrix;

DataType** MatrixBuild(int row, int column){
    DataType** matrixResult = (DataType**)calloc(row, sizeof(DataType*));
    for(int i = 0; i < row; i++){
        *(matrixResult + i) = (DataType*)calloc(column, sizeof(DataType));
    }
    return matrixResult;
}

void CompressDim2Matrix(DataType** origin, int originRow, int originCol, CompressMatrix* result){
    int index = 0;
    for(int i = 0; i < originRow; i++){
        for(int j = 0; j < originCol; j++){
            if(*(*(origin + i) + j) != 0){
                result->matrix[index].data = *(*(origin + i) + j);
                result->matrix[index].rowIndex = i;
                result->matrix[index].colIndex = j;
                result->rowNumber++;
                result->colNumber++;
                result->totalNumber++;
            }
        }
    }
}

void TranslateCompressedMatrix(CompressMatrix origin, CompressMatrix* transformed){
    transformed->colNumber = origin.rowNumber;
    transformed->rowNumber = origin.colNumber;
    transformed->totalNumber = origin.totalNumber;
    int* number = (int*)calloc(origin.colNumber, sizeof(int));
    int* start = (int*)calloc(origin.colNumber, sizeof(int));
    *start = 0;
    for(int i = 0; i < origin.colNumber; i++){
        *(number + i) = 0;
    }
    for(int i = 0; i < origin.totalNumber; i++){
        (*(number + origin.matrix[i].colIndex))++;
    }
    for(int i = 1; i < origin.totalNumber; i++){
        *(start + i) = *(start + i - 1) + *(number + i - 1);
    }
    for(int i = 0; i < origin.totalNumber; i++){
        int index = *(start + origin.matrix[i].colIndex);
        (*(start + origin.matrix[i].colIndex))++;
        transformed->matrix[index].data = origin.matrix[i].data;
        transformed->matrix[index].colIndex = origin.matrix[i].rowIndex;
        transformed->matrix[index].rowIndex = origin.matrix[i].colIndex;
    }
}

void VisualCompressedMatrix(CompressMatrix matrix){
    int index = 0;
    for(int i = 0; i < matrix.rowNumber; i++){
        for(int j = 0; j < matrix.colNumber; j++){
            if(matrix.matrix[index].rowIndex == i && matrix.matrix[index].colIndex == j){
                printf("%d\t", matrix.matrix[index].data);
                index++;
            }
            else{
                printf("0\t");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int CompressedMatrixMultiply(CompressMatrix matrix01, CompressMatrix matrix02, CompressMatrix* resultMatrix){
    if(matrix01.colNumber != matrix02.rowNumber){
        printf("Dim Wrong!");
        return 0;
    }
    else{
        resultMatrix->rowNumber = matrix01.rowNumber;
        resultMatrix->colNumber = matrix02.colNumber;
        CompressMatrix matrix02T;
        TranslateCompressedMatrix(matrix02, &matrix02T);
        int* number01 = (int*)calloc(matrix01.rowNumber, sizeof(int));
        int* number02 = (int*)calloc(matrix02T.rowNumber, sizeof(int));
        int* index01 = (int*)calloc(matrix01.rowNumber, sizeof(int));
        int* index02 = (int*)calloc(matrix02T.rowNumber, sizeof(int));
        *index01 = 0;
        *index02 = 0;
        for(int i = 1; i < matrix01.rowNumber; i++){
            *(index01 + i) = *(index01 + i - 1) + *(number01 + i);
        }
        for(int i = 1; i < matrix02T.rowNumber; i++){
            *(index02 + i) = *(index02 + i - 1) + *(number02 + i);
        }
        for(int i = 0; i < matrix01.totalNumber; i++){
            (*(number01 + matrix01.matrix[i].rowIndex))++;
        }
        for(int i = 0; i < matrix02T.totalNumber; i++){
            (*(number02 + matrix02T.matrix[i].rowIndex))++;
        }
        for(int i = 0; i < matrix01.rowNumber; i++){
            for(int j = 0; j < matrix02T.rowNumber; j++){

            }
        }
    }
}

void main(){
    int size = 3;
    CompressMatrix matrix01;
    CompressMatrix matrix02;

    matrix01.colNumber = size;
    matrix01.rowNumber = size;
    matrix01.totalNumber = 0;
    int index01 = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int input;
            printf("please input %d number\n", i*size + j);
            scanf("%d", &input);
            if(input != 0){
                matrix01.matrix[index01].data = input;
                matrix01.matrix[index01].colIndex = j;
                matrix01.matrix[index01].rowIndex = i;
                matrix01.totalNumber++;
                index01++;
            }
        }
    }

    VisualCompressedMatrix(matrix01);
    CompressMatrix matrix01T;
    TranslateCompressedMatrix(matrix01, &matrix01T);
    VisualCompressedMatrix(matrix01T);


    matrix02.colNumber = size;
    matrix02.rowNumber = size;
}
