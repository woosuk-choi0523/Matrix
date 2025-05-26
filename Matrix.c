#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

void InitVector(Vector* vector, int Length) {
    vector->length = Length;
    vector->Vector = (float*) malloc(Length * sizeof(float));
    for (int i = 0; i < Length; i++) {
        vector->Vector[i] = 0;
    }
}

void FreeVector(Vector* vector) {
    free(vector->Vector);
}

Vector ScaleVector(Vector vector, float Scalar) {
    Vector result;
    InitVector(&result, vector.length);
    for (int i = 0; i < vector.length; i++) {
        result.Vector[i] = vector.Vector[i] * Scalar;
    }
    return result;
}

Vector AddVector(Vector vector1, Vector vector2) {
    Vector result;
    InitVector(&result, vector1.length);
    for (int i = 0; i < vector1.length; i++) {
        result.Vector[i] = vector1.Vector[i] + vector2.Vector[i];
    }
    return result;
}

void PrintVector(Vector vector) {
    for (int i = 0; i < vector.length; i++) {
        printf("(%f)\n", vector.Vector[i]);
    }
}

Vector SubtractVector(Vector vector1, Vector vector2) {
    Vector result;
    InitVector(&result, vector1.length);
    for (int i = 0; i < vector1.length; i++) {
        result.Vector[i] = vector1.Vector[i] - vector2.Vector[i];
    }
    return result;
}

float DotProduct(Vector vector1, Vector vector2) {
    float result = 0;
    for (int i = 0; i < vector1.length; i++) {
        result += vector1.Vector[i] * vector2.Vector[i];
    }
    return result;
}

void InitMatrix(Matrix *Mat, int rows, int cols) {
    Mat->rows = rows;
    Mat->cols = cols;
    Mat->matrix = (float *)malloc(rows * cols * sizeof(float));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            EditMatrix(Mat, i, j, 0);
        }
    }
}

void FreeMatrix(Matrix *Mat) {
    if (Mat->matrix != NULL) {
        free(Mat->matrix);
        Mat->matrix = NULL;
        }
    Mat->rows = 0;
    Mat->cols = 0;
}

int GetMatrixValue(Matrix Mat, int row, int col) {
    return Mat.matrix[row*Mat.cols+col];
}

void EditMatrix(Matrix *Mat, int row, int col, float value) {
    if (row < 0 || row >= Mat->rows || col < 0 || col >= Mat->cols) {
        printf("Matrix out of bounds\n");
        exit(1);
    }
    Mat->matrix[row*Mat->cols+col] = value;
}

void PrintMatrix(Matrix Mat) {
    for (int i = 0; i < Mat.rows; i++) {
        printf("[");
        for (int j = 0; j < Mat.cols; j++) {
            printf("%f ", Mat.matrix[i*Mat.cols+j]);
            }
        printf("]\n");
        }
}

Matrix MatrixMultiply_Mat(Matrix Mat1, Matrix Mat2) {
    Matrix result;
    if (Mat1.cols != Mat2.rows) {
        printf("Matrix Multiplication Error");
        exit(1);
        }
    InitMatrix(&result, Mat1.rows, Mat2.cols);
    for (int i = 0; i < Mat1.rows; i++) {
        for (int j = 0; j < Mat2.cols; j++) {
            for (int k = 0; k < Mat1.cols; k++) {
                result.matrix[i*Mat2.cols+j] += Mat1.matrix[i*Mat1.cols + k] * Mat2.matrix[k*Mat2.cols + j];
                }
            }
        }
    return result;
}

Vector MatrixMultiply_Vec(Matrix Mat1, Vector vector) {
    Vector result;
    if (Mat1.cols != vector.length) {
        printf("Matrix Multiplication Error");
        exit(1);
    }
    InitVector(&result, Mat1.rows);
    for (int i = 0; i < Mat1.rows; i++) {
        for (int j = 0; j < Mat1.cols; j++) {
            result.Vector[i] += vector.Vector[j] * Mat1.matrix[i*Mat1.cols + j];
        }
    }
    return result;
}

