#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

typedef struct {
    int rows;
    int cols;
    int *matrix;
} Matrix;

// 행렬 초기화 함수
void MatrixInit(Matrix *Mat, int rows, int cols);

// 행렬에서 특정 위치의 값을 가져오는 함수
int MatrixValue(Matrix *Mat, int row, int col);

// 행렬의 특정 위치 값을 수정하는 함수
void MatrixEdit(Matrix *Mat, int row, int col, int value);

#endif // MATRIX_H