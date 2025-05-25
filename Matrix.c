#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

void VectorInit(Vector* Vector, int Length) {
    Vector->length = Length;
    Vector->Vector = (float*) malloc(Length * sizeof(float));
    for (int i = 0; i < Length; i++) {
        Vector->Vector[i] = 0;
    }
}

Vector VectorMultply(Vector vector, float Scalar) {
    Vector result;
    VectorInit(&result, vector.length);
    for (int i = 0; i < vector.length; i++) {
        result.Vector[i] = vector.Vector[i] * Scalar;
    }
    return result;
}

Vector VectorAdd(Vector vector1, Vector vector2) {
    Vector result;
    VectorInit(&result, vector1.length);
    for (int i = 0; i < vector1.length; i++) {
        result.Vector[i] = vector1.Vector[i] + vector2.Vector[i];
    }
    return result;
}

Vector VectorSubtract(Vector vector1, Vector vector2) {
    Vector result;
    VectorInit(&result, vector1.length);
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

void MatrixInit(Matrix *Mat, int rows, int cols) {
    Mat->rows = rows;
    Mat->cols = cols;
    Mat->matrix = (int *)malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            MatrixEdit(Mat, i, j, 0);
        }
    }
}

void MatrixFree(Matrix *Mat) {
    if (Mat->matrix != NULL) {
        free(Mat->matrix);
        Mat->matrix = NULL;
    }
    Mat->rows = 0;
    Mat->cols = 0;
}

int MatrixValue(Matrix Mat, int row, int col) {
    return Mat.matrix[row*Mat.cols+col];
}

void MatrixEdit(Matrix *Mat, int row, int col, int value) {
    if (row < 0 || row >= Mat->rows || col < 0 || col >= Mat->cols) {
        exit(1);
    }
    Mat->matrix[row*Mat->cols+col] = value;
}

void MatrixPrint(Matrix Mat) {
    for (int i = 0; i < Mat.rows; i++) {
        for (int j = 0; j < Mat.cols; j++) {
            printf("%d ", Mat.matrix[i*Mat.cols+j]);
        }
        printf("\n");
    }
}

Matrix MatrixMultiply(Matrix Mat1, Matrix Mat2) {
    Matrix result;
    if (Mat1.cols != Mat2.rows) {
        printf("Matrix Multiplication Error");
        exit(1);
    }
    MatrixInit(&result, Mat1.rows, Mat2.cols);
    for (int i = 0; i < Mat1.rows; i++) {
        for (int j = 0; j < Mat2.cols; j++) {
         for (int k = 0; k < Mat1.cols; k++) {
             result.matrix[i*Mat2.cols+j] += Mat1.matrix[i*Mat1.cols + k] * Mat2.matrix[k*Mat2.cols + j];
         }
        }
    }
    return result;
}