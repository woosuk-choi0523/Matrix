#include "Matrix.h"
#include "Ai.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void InitAI(AI* Ai, int input_Number, int Hiddenlayer_Number ,int* Hiddenlayer_Neuron_Number, int output_Number) {
    Ai->Hiddenlayer_Neuron_Number = Hiddenlayer_Neuron_Number;
    Ai->Hiddenlayer_Number = Hiddenlayer_Number;
    Ai->input_Number = input_Number;
    Ai->output_Number = output_Number;
    Ai->Weights = malloc((Ai->Hiddenlayer_Number + 1) * sizeof(Matrix));
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
            MatrixInit(&Ai->Weights[i], Ai->Hiddenlayer_Neuron_Number[i + 1],
                       (i == 0) ? Ai->input_Number : Ai->Hiddenlayer_Neuron_Number[i]);
        }
    Ai->Biases = malloc((Ai->Hiddenlayer_Number + 1) * sizeof(Vector));
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        VectorInit(&Ai->Biases[i], Ai->Hiddenlayer_Number[i]);
    }
}

void FreeAI(AI* Ai) {
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        MatrixFree(&Ai->Weights[i]);
        VectorFree(&Ai->Biases[i]);
    }
    free(Ai->Weights);
    free(Ai->Biases);
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        VectorInit(&Ai->Biases[i], Ai->Hiddenlayer_Neuron_Number[i]);
    }
}

void FreeAI(AI* Ai) {
    free(Ai->Weights);
    free(Ai->Biases);
    free(Ai->Hiddenlayer_Neuron_Number);
}

void SetWeights(AI* Ai, Matrix matrix, int Weight_Number) {
    Ai->Weights[Weight_Number] = matrix;
}

void SetBiases(AI* Ai, Matrix matrix, int Bias_Number) {
    Ai->Biases[Bias_Number] = matrix;
}

double Sigmoid(float x) {
    return 1.0 / (1.0 + expf(-x));
}



Vector Forward(AI* Ai, Vector input) {
    Vector output;
    VectorInit(&output, Ai->output_Number);
    for (int i = 0; i < Ai->Hiddenlayer_Number; i++) {

    }
    return output;
}