#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

#define  MatrixMultiply(x, y)_Generic((y), \
Matrix: MatrixMultiply_Mat, \
Vector: MatrixMultiply_Vec)(x, y)

typedef struct {
    int length;
    float* Vector;
}Vector;

typedef struct {
    int rows;
    int cols;
    float *matrix;
} Matrix;

void VectorInit(Vector* Vector, int Length);

void VectorFree(Vector* vector);

Vector VectorAdd(Vector vector1, Vector vector2);

Vector VectorSubtract(Vector vector1, Vector vector2);

Vector VectorScale(Vector vector, float Scalar);

void PrintVector(Vector vector);

float DotProduct(Vector vector1, Vector vector2) ;

// 행렬 초기화
void MatrixInit(Matrix *Mat, int rows, int cols);

// 행렬 메모리 해제
void MatrixFree(Matrix *Mat);

// 행렬에서 특정 위치의 값을 가져오기
int MatrixValue(Matrix Mat, int row, int col);

// 행렬의 특정 위치 값을 수정
void MatrixEdit(Matrix *Mat, int row, int col, float value);

// 행렬 출력
void MatrixPrint(Matrix Mat);

// 행렬 곱
Matrix MatrixMultiply_Mat(Matrix Mat1, Matrix Mat2);
Vector MatrixMultiply_Vec(Matrix Mat, Vector Vector);

#endif // MATRIX_LIBRARY_H
