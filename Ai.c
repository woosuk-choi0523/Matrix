#include "Matrix.h"
#include "Ai.h"
#include <stdio.h>
#include <stdlib.h>

void InitAI(AI* Ai, int* Hiddenlayer_Neuron_Number) {
    Ai->Hiddenlayer_Neuron_Number = Hiddenlayer_Neuron_Number;
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
}