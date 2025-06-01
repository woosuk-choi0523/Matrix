#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 벡터 구조체를 초기화하고 메모리를 할당합니다.
 *
 * 이 함수는 주어진 길이에 맞춰 Vector 구조체의 메모리를 동적으로 할당하고,
 * 할당된 모든 요소를 0으로 초기화합니다.
 *
 * @param vector 초기화할 Vector 구조체에 대한 포인터입니다.
 * @param Length 벡터에 할당할 요소의 개수(길이)입니다.
 *
 * @note 메모리 할당에 실패하면 프로그램이 종료됩니다. (exit(EXIT_FAILURE))
 * @warning 이 함수로 할당된 메모리는 사용 후 반드시 FreeVector() 함수로 해제해야 합니다.
 * (예: `FreeVector(&vector);`)
 */
void InitVector(Vector* vector, int Length) {
    vector->length = Length;
    vector->Vector = (float*) malloc(Length * sizeof(float));
    for (int i = 0; i < Length; i++) {
        vector->Vector[i] = 0;
    }
}

/**
 * @brief 벡터 구조체에 할당된 메모리를 해제합니다.
 *
 * 이 함수는 InitVector() 함수로 동적 할당된 벡터의 메모리를 해제하고,
 * 벡터의 포인터를 NULL로 설정하며 길이를 0으로 초기화합니다.
 *
 * @param vector 메모리를 해제할 Vector 구조체에 대한 포인터입니다.
 */
void FreeVector(Vector* vector) {
    free(vector->Vector);
    vector->Vector = NULL;
    vector->length = 0;
}


/**
 * @brief 백터에 스칼라를 곱하는 것을 처리합니다.
 *
 * 이 함수는 주어진 길이에 맞춰 Vector 구조체의 메모리를 동적으로 할당하고,
 * 할당된 모든 요소를 0으로 초기화합니다.
 *
 * @param vector 초기화할 Vector 구조체에 대한 포인터입니다.
 * @param Length 벡터에 할당할 요소의 개수(길이)입니다.
 *
 * @note 메모리 할당에 실패하면 프로그램이 종료됩니다. (exit(EXIT_FAILURE))
 * @warning 이 함수로 할당된 메모리는 사용 후 반드시 FreeVector() 함수로 해제해야 합니다.
 * (예: `FreeVector(&vector);`)
 */
Vector ScaleVector(Vector vector, float Scalar) {
    Vector result;
    InitVector(&result, vector.length);
    for (int i = 0; i < vector.length; i++) {
        result.Vector[i] = vector.Vector[i] * Scalar;
    }
    return result;
}

/**
 * @brief 두 벡터를 더한 새로운 벡터를 반환합니다.
 *
 * 이 함수는 두 개의 벡터를 요소별로 더하여 새로운 벡터를 생성하고 반환합니다.
 * 두 벡터의 길이가 같아야 합니다.
 *
 * @param vector1 첫 번째 Vector 구조체입니다.
 * @param vector2 두 번째 Vector 구조체입니다.
 *
 * @return 두 벡터의 합으로 구성된 새로운 Vector 구조체입니다.
 * @warning 반환된 벡터는 함수 내부에서 동적으로 메모리가 할당되므로,
 * 사용 후 반드시 FreeVector() 함수로 해제해야 합니다.
 */
Vector AddVector(Vector vector1, Vector vector2) {
    if (vector1.length != vector2.length) {
        printf("Vector length mismatch\n");
        exit(1);
    }
    Vector result;
    InitVector(&result, vector1.length);
    for (int i = 0; i < vector1.length; i++) {
        result.Vector[i] = vector1.Vector[i] + vector2.Vector[i];
    }
    return result;
}

/**
 * @brief 벡터의 모든 요소를 표준 출력에 출력합니다.
 *
 * 각 벡터 요소는 별도의 줄에 표시됩니다.
 *
 * @param vector 출력할 Vector 구조체입니다.
 */
void PrintVector(Vector vector) {
    if (vector.length == 0) {
        printf("Vector is empty\n");
    }
    for (int i = 0; i < vector.length; i++) {
        printf("(%f)\n", vector.Vector[i]);
    }
}

/**
 * @brief 두 벡터를 뺀 새로운 벡터를 반환합니다.
 *
 * 이 함수는 첫 번째 벡터에서 두 번째 벡터를 요소별로 빼서 새로운 벡터를 생성하고 반환합니다.
 * 두 벡터의 길이가 같아야 합니다.
 *
 * @param vector1 첫 번째 Vector 구조체입니다 (피감수 벡터).
 * @param vector2 두 번째 Vector 구조체입니다 (감수 벡터).
 *
 * @return 두 벡터의 차이로 구성된 새로운 Vector 구조체입니다.
 * @warning 반환된 벡터는 함수 내부에서 동적으로 메모리가 할당되므로,
 * 사용 후 반드시 FreeVector() 함수로 해제해야 합니다..
 */
Vector SubtractVector(Vector vector1, Vector vector2) {
    if (vector1.length != vector2.length) {
        printf("Vector length mismatch\n");
        exit(EXIT_FAILURE);
    }
    Vector result;
    InitVector(&result, vector1.length);
    for (int i = 0; i < vector1.length; i++) {
        result.Vector[i] = vector1.Vector[i] - vector2.Vector[i];
    }
    return result;
}

/**
 * @brief 두 벡터의 내적(Dot Product)을 계산합니다.
 *
 * 이 함수는 두 벡터의 내적 값을 계산하여 반환합니다.
 * 두 벡터의 길이가 같아야 합니다.
 *
 * @param vector1 첫 번째 Vector 구조체입니다.
 * @param vector2 두 번째 Vector 구조체입니다.
 *
 * @return 두 벡터의 내적 값(float)입니다.
 * @note 두 벡터의 길이가 다를 경우, 결과가 정확하지 않거나
 * 예상치 못한 동작이 발생할 수 있습니다.
 */
float DotProduct(Vector vector1, Vector vector2) {
    if (vector1.length != vector2.length) {
        printf("Vector length mismatch\n");
        exit(EXIT_FAILURE);
    }
    float result = 0;
    for (int i = 0; i < vector1.length; i++) {
        result += vector1.Vector[i] * vector2.Vector[i];
    }
    return result;
}

/**
 * @brief 행렬 구조체를 초기화하고 메모리를 할당합니다.
 *
 * 이 함수는 주어진 행과 열의 크기에 맞춰 Matrix 구조체의 메모리를 동적으로 할당하고,
 * 할당된 모든 요소를 0으로 초기화합니다.
 *
 * @param Mat 초기화할 Matrix 구조체에 대한 포인터입니다.
 * @param rows 행렬의 행(row) 개수입니다.
 * @param cols 행렬의 열(column) 개수입니다.
 *
 * @warning 이 함수로 할당된 메모리는 사용 후 반드시 FreeMatrix() 함수로 해제해야 합니다.
 * (예: `FreeMatrix(&myMatrix);`)
 */
void InitMatrix(Matrix *Mat, int rows, int cols) {
    Mat->rows = rows;
    Mat->cols = cols;
    Mat->Matrix = malloc(rows * cols * sizeof(float));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            EditMatrix(Mat, i, j, 0);
        }
    }
}

/**
 * @brief 행렬 구조체에 할당된 메모리를 해제합니다.
 *
 * 이 함수는 InitMatrix() 함수로 동적 할당된 행렬의 메모리를 해제하고,
 * 행렬 포인터를 NULL로 설정하며 행과 열의 크기를 0으로 초기화합니다.
 *
 * @param Mat 메모리를 해제할 Matrix 구조체에 대한 포인터입니다.
 */
void FreeMatrix(Matrix *Mat) {
    if (Mat->Matrix != NULL) {
        free(Mat->Matrix);
        Mat->Matrix = NULL;
        }
    Mat->rows = 0;
    Mat->cols = 0;
}

/**
 * @brief 행렬에서 특정 위치의 값을 가져옵니다.
 *
 * @param Mat 값을 가져올 Matrix 구조체입니다.
 * @param row 가져올 요소의 행(row) 인덱스입니다.
 * @param col 가져올 요소의 열(column) 인덱스입니다.
 *
 * @return 해당 행렬 위치의 값(int)입니다. (현재 float 타입 반환이 더 적절해 보입니다).
 */
float GetMatrixValue(Matrix Mat, int row, int col) {
    if (Mat.Matrix == NULL) {
        printf("Matrix is empty\n");
        exit(EXIT_FAILURE);
    }
    if (row < 0 || row >= Mat.rows) {
        printf("Row index mismatch\n");
        exit(EXIT_FAILURE);
    }
    if (col < 0 || col >= Mat.cols) {
        printf("Column index mismatch\n");
        exit(EXIT_FAILURE);
    }
    return Mat.Matrix[row*Mat.cols+col];
}

/**
 * @brief 행렬의 특정 위치 값을 수정합니다.
 *
 * 이 함수는 주어진 행, 열 인덱스에 해당하는 행렬 요소를 새로운 값으로 설정합니다.
 * 유효하지 않은 인덱스인 경우 오류 메시지를 출력하고 프로그램을 종료합니다.
 *
 * @param Mat 값을 수정할 Matrix 구조체에 대한 포인터입니다.
 * @param row 수정할 요소의 행(row) 인덱스입니다.
 * @param col 수정할 요소의 열(column) 인덱스입니다.
 * @param value 해당 위치에 설정할 실수(float) 값입니다.
 */
void EditMatrix(Matrix *Mat, int row, int col, float value) {
    if (row < 0 || row >= Mat->rows || col < 0 || col >= Mat->cols) {
        printf("Matrix out of bounds\n");
        exit(1);
    }
    Mat->Matrix[row*Mat->cols+col] = value;
}

/**
 * @brief 행렬의 모든 요소를 표준 출력에 출력합니다.
 *
 * 행렬의 각 행은 대괄호 `[]`로 묶여 표시됩니다.
 *
 * @param Mat 출력할 Matrix 구조체입니다.
 */
void PrintMatrix(Matrix Mat) {
    for (int i = 0; i < Mat.rows; i++) {
        printf("[");
        for (int j = 0; j < Mat.cols; j++) {
            printf("%f ", Mat.Matrix[i*Mat.cols+j]);
            }
        printf("]\n");
        }
}

/**
 * @brief 두 행렬의 곱셈을 수행하여 새로운 행렬을 반환합니다.
 *
 * 이 함수는 첫 번째 행렬(Mat1)과 두 번째 행렬(Mat2)의 곱셈을 수행합니다.
 * Mat1의 열(cols) 수와 Mat2의 행(rows) 수가 같아야 합니다.
 * 그렇지 않으면 오류 메시지를 출력하고 프로그램을 종료합니다.
 *
 * @param Mat1 첫 번째 Matrix 구조체입니다.
 * @param Mat2 두 번째 Matrix 구조체입니다.
 *
 * @return 곱셈 결과로 생성된 새로운 Matrix 구조체입니다.
 * @warning 반환된 행렬은 함수 내부에서 동적으로 메모리가 할당되므로,
 * 사용 후 반드시 FreeMatrix() 함수로 해제해야 합니다.
 */
Matrix MultiplyMatrix_Mat(Matrix Mat1, Matrix Mat2) {
    Matrix result;
    if (Mat1.cols != Mat2.rows) {
        printf("Matrix Multiplication Error");
        exit(1);
        }
    InitMatrix(&result, Mat1.rows, Mat2.cols);
    for (int i = 0; i < Mat1.rows; i++) {
        for (int j = 0; j < Mat2.cols; j++) {
            for (int k = 0; k < Mat1.cols; k++) {
                result.Matrix[i*Mat2.cols+j] += Mat1.Matrix[i*Mat1.cols + k] * Mat2.Matrix[k*Mat2.cols + j];
                }
            }
        }
    return result;
}
/**
* @brief 행렬과 벡터의 곱셈을 수행하여 새로운 벡터를 반환합니다.
*
* 이 함수는 행렬(Mat1)과 벡터(vector)의 곱셈을 수행합니다.
* 행렬의 열(cols) 수와 벡터의 길이(length)가 같아야 합니다.
* 그렇지 않으면 오류 메시지를 출력하고 프로그램을 종료합니다.
*
* @param Mat1 Matrix 구조체입니다.
* @param vector Vector 구조체입니다.
*
* @return 곱셈 결과로 생성된 새로운 Vector 구조체입니다.
* @warning 반환된 벡터는 함수 내부에서 동적으로 메모리가 할당되므로,
* 사용 후 반드시 FreeVector() 함수로 해제해야 합니다.
*/
Vector MultiplyMatrix_Vec(Matrix Mat1, Vector vector) {
    Vector result;
    if (Mat1.cols != vector.length) {
        printf("Matrix Multiplication Error");
        exit(1);
    }
    InitVector(&result, Mat1.rows);
    for (int i = 0; i < Mat1.rows; i++) {
        for (int j = 0; j < Mat1.cols; j++) {
            result.Vector[i] += vector.Vector[j] * Mat1.Matrix[i*Mat1.cols + j];
        }
    }
    return result;
}

