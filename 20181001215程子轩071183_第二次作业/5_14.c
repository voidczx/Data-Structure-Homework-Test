#include<stdio.h>
#include<malloc.h>

typedef int DataType;

DataType** MatrixBuild(int row, int column){
    DataType** matrixResult = (DataType**)calloc(row, sizeof(DataType*));
    for(int i = 0; i < row; i++){
        *(matrixResult + i) = (DataType*)calloc(column, sizeof(DataType));
    }
    return matrixResult;
}

DataType** MatrixAdd(DataType**matrix01, DataType**matrix02, int N){

    DataType** matrixAdd;
    matrixAdd = MatrixBuild(N, N);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            *(*(matrixAdd + i) + j) = *(*(matrix01 + i) + j) + *(*(matrix02 + i) + j);
        }
    }

    return matrixAdd;
}

void VisualMatrix(DataType** matrix, int row, int column){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("%d\t", *(*(matrix+i)+j));
        }
        printf("\n");
    }
    printf("\n\n");
}

void main(){
    int size = 5;
    DataType** matrix01;
    DataType** matrix02;
    DataType** result;
    matrix01 = MatrixBuild(size, size);
    matrix02 = MatrixBuild(size, size);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            *(*(matrix01 + i) + j) = i * size + j;
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            *(*(matrix02 + i) + j) = (i * size + j) + 1;
        }
    }

    VisualMatrix(matrix01, size, size);
    VisualMatrix(matrix02, size, size);

    result = MatrixAdd(matrix01, matrix02, size);
    VisualMatrix(result, size, size);
}
