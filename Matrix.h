#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

// _Generic 매크로를 사용하여 오버로딩된 MatrixMultiply 함수를 제공합니다.
// 첫 번째 인자(x)는 Matrix여야 하며, 두 번째 인자(y)의 타입에 따라
// MatrixMultiply_Mat 또는 MatrixMultiply_Vec 함수가 호출됩니다.
#define  MultiplyMatrix(x, y)_Generic((y), \
Matrix: MultiplyMatrix_Mat, \
Vector: MultiplyMatrix_Vec)(x, y)

/**
 * @brief 벡터를 표현하는 구조체입니다.
 */
typedef struct {
    int length;     /**< 벡터의 길이(요소의 개수)입니다. */
    float* Vector;  /**< 벡터 요소를 저장하는 동적 할당된 배열에 대한 포인터입니다. */
}Vector;

/**
 * @brief 행렬을 표현하는 구조체입니다.
 */
typedef struct {
    int rows;       /**< 행렬의 행(row) 개수입니다. */
    int cols;       /**< 행렬의 열(column) 개수입니다. */
    float *Matrix;  /**< 행렬 요소를 저장하는 동적 할당된 1차원 배열에 대한 포인터입니다. */
} Matrix;

/**
 * @brief 벡터 구조체를 초기화하고 메모리를 할당합니다.
 * @param vector 초기화할 Vector 구조체에 대한 포인터입니다.
 * @param Length 벡터에 할당할 요소의 개수(길이)입니다.
 */
void InitVector(Vector* Vector, int Length);

/**
 * @brief 벡터 구조체에 할당된 메모리를 해제합니다.
 * @param vector 메모리를 해제할 Vector 구조체에 대한 포인터입니다.
 */
void FreeVector(Vector* vector);

/**
 * @brief 두 벡터를 더한 새로운 벡터를 반환합니다.
 * @param vector1 첫 번째 Vector 구조체입니다.
 * @param vector2 두 번째 Vector 구조체입니다.
 * @return 두 벡터의 합으로 구성된 새로운 Vector 구조체입니다.
 */
Vector AddVector(Vector vector1, Vector vector2);

/**
 * @brief 두 벡터를 뺀 새로운 벡터를 반환합니다.
 * @param vector1 첫 번째 Vector 구조체입니다.
 * @param vector2 두 번째 Vector 구조체입니다.
 * @return 두 벡터의 차이로 구성된 새로운 Vector 구조체입니다.
 */

Vector SubtractVector(Vector vector1, Vector vector2);

/**
 * @brief 벡터에 스칼라 값을 곱한 새로운 벡터를 반환합니다.
 * @param vector 스칼라를 곱할 원본 Vector 구조체입니다.
 * @param Scalar 벡터의 각 요소에 곱할 실수(float) 값입니다.
 * @return 각 요소에 스칼라가 곱해진 새로운 Vector 구조체입니다.
 */
Vector ScaleVector(Vector vector, float Scalar);

/**
 * @brief 벡터의 모든 요소를 표준 출력에 출력합니다.
 * @param vector 출력할 Vector 구조체입니다.
 */
void PrintVector(Vector vector);

/**
 * @brief 두 벡터의 내적(Dot Product)을 계산합니다.
 * @param vector1 첫 번째 Vector 구조체입니다.
 * @param vector2 두 번째 Vector 구조체입니다.
 * @return 두 벡터의 내적 값(float)입니다.
 */
float DotProduct(Vector vector1, Vector vector2) ;

/**
 * @brief 행렬 구조체를 초기화하고 메모리를 할당합니다.
 * @param Mat 초기화할 Matrix 구조체에 대한 포인터입니다.
 * @param rows 행렬의 행(row) 개수입니다.
 * @param cols 행렬의 열(column) 개수입니다.
 */
void InitMatrix(Matrix *Mat, int rows, int cols);

/**
 * @brief 행렬 구조체에 할당된 메모리를 해제합니다.
 * @param Mat 메모리를 해제할 Matrix 구조체에 대한 포인터입니다.
 */
void FreeMatrix(Matrix *Mat);

/**
 * @brief 행렬에서 특정 위치의 값을 가져옵니다.
 * @param Mat 값을 가져올 Matrix 구조체입니다.
 * @param row 가져올 요소의 행(row) 인덱스입니다.
 * @param col 가져올 요소의 열(column) 인덱스입니다.
 * @return 해당 행렬 위치의 값(float)입니다.
 */
float GetMatrixValue(Matrix Mat, int row, int col);

/**
 * @brief 행렬의 특정 위치 값을 수정합니다.
 * @param Mat 값을 수정할 Matrix 구조체에 대한 포인터입니다.
 * @param row 수정할 요소의 행(row) 인덱스입니다.
 * @param col 수정할 요소의 열(column) 인덱스입니다.
 * @param value 해당 위치에 설정할 실수(float) 값입니다.
 */
void EditMatrix(Matrix *Mat, int row, int col, float value);

/**
 * @brief 행렬의 모든 요소를 표준 출력에 출력합니다.
 * @param Mat 출력할 Matrix 구조체입니다.
 */
void PrintMatrix(Matrix Mat);

/**
 * @brief 두 행렬의 곱셈을 수행하여 새로운 행렬을 반환합니다.
 * @param Mat1 첫 번째 Matrix 구조체입니다.
 * @param Mat2 두 번째 Matrix 구조체입니다.
 * @return 곱셈 결과로 생성된 새로운 Matrix 구조체입니다.
 */
Matrix MultiplyMatrix_Mat(Matrix Mat1, Matrix Mat2);
/**
 * @brief 행렬과 벡터의 곱셈을 수행하여 새로운 벡터를 반환합니다.
 * @param Mat 행렬 구조체입니다.
 * @param Vector 벡터 구조체입니다.
 * @return 곱셈 결과로 생성된 새로운 Vector 구조체입니다.
 */
Vector MultiplyMatrix_Vec(Matrix Mat, Vector Vector);

#endif // MATRIX_LIBRARY_H
