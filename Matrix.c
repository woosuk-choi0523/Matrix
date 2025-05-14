#include "Matrix.h"
#include <stdio.h>

struct Matrix{
    int rows;
    int cols;
    int *matrix;
};

int MatrixValue(struct Matrix Mat, int row, int col) {
    return Mat.matrix[row*Mat.cols+col];
}

void MatrixEdit(struct Matrix Mat, int row, int col, int value) {
    Mat.matrix[row*Mat.cols+col] = value;
}
