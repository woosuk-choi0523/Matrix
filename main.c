#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

int main() {
    Matrix Mat1, Mat2;
    MatrixInit(&Mat1,3,2);
    MatrixInit(&Mat2,2,2);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            MatrixEdit(&Mat1, i, j, i+j+1);
        }
    }
    MatrixPrint(Mat1);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            MatrixEdit(&Mat2, i, j, i-j+1);
        }
    }
    MatrixPrint(Mat2);
    Matrix Mat3 = MatrixMultiply(Mat1, Mat2);
    MatrixPrint(Mat3);
    return 0;
}