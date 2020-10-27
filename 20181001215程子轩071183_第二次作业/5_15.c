#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

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
    result->rowNumber = originRow;
    result->colNumber = originCol;
    for(int i = 0; i < originRow; i++){
        for(int j = 0; j < originCol; j++){
            if(*(*(origin + i) + j) != 0){
                result->matrix[index].data = *(*(origin + i) + j);
                result->matrix[index].rowIndex = i;
                result->matrix[index].colIndex = j;
                result->totalNumber++;
                index++;
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
    free(number);
    free(start);
}

DataType** UncompressMatrix(CompressMatrix matrix){
    DataType** result;
    int** flag;
    flag = (DataType**)calloc(matrix.rowNumber, sizeof(int*));
    for(int i = 0; i < matrix.rowNumber; i++){
        *(flag + i) = (DataType*)calloc(matrix.colNumber, sizeof(int));
    }
    result = MatrixBuild(matrix.rowNumber, matrix.colNumber);
    for(int i = 0; i < matrix.totalNumber; i++){
        MatrixElement element = matrix.matrix[i];
        *(*(result + element.rowIndex) + element.colIndex) = element.data;
        *(*(flag + element.rowIndex) + element.colIndex) = 1;
    }
    for(int i = 0; i < matrix.rowNumber; i++){
        for(int j = 0; j < matrix.colNumber; j++){
            if(*(*(flag + i) + j) != 1){
                *(*(result + i) + j) = 0;
            }
        }
    }
    return result;
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
        resultMatrix->totalNumber = 0;
        CompressMatrix matrix02T;
        TranslateCompressedMatrix(matrix02, &matrix02T);
        DataType** tempMatrix01;
        DataType** tempMatrix02;
        tempMatrix01 = UncompressMatrix(matrix01);
        tempMatrix02 = UncompressMatrix(matrix02T);
        for(int i = 0; i < matrix01.rowNumber; i++){
            for(int j = 0; j < matrix02T.rowNumber; j++){
                DataType temp = 0;
                for(int k = 0; k < matrix01.colNumber; k++){
                    temp += (*(*(tempMatrix01 + i) + k)) * (*(*(tempMatrix02 + j) + k));
                }
                resultMatrix->matrix[resultMatrix->totalNumber].rowIndex = i;
                resultMatrix->matrix[resultMatrix->totalNumber].colIndex = j;
                resultMatrix->matrix[resultMatrix->totalNumber].data = temp;
                resultMatrix->totalNumber++;
            }
        }
        return 1;
    }
}

void main(){
    int size = 2;
    CompressMatrix matrix01;
    CompressMatrix matrix02;
    CompressMatrix result;

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

    matrix02.colNumber = size;
    matrix02.rowNumber = size;
    matrix02.totalNumber = 0;
    int index02 = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int input;
            printf("please input %d number\n", i*size + j);
            scanf("%d", &input);
            if(input != 0){
                matrix02.matrix[index02].data = input;
                matrix02.matrix[index02].colIndex = j;
                matrix02.matrix[index02].rowIndex = i;
                matrix02.totalNumber++;
                index02++;
            }
        }
    }

    VisualCompressedMatrix(matrix01);
    VisualCompressedMatrix(matrix02);
    CompressedMatrixMultiply(matrix01, matrix02, &result);
    VisualCompressedMatrix(result);

}
