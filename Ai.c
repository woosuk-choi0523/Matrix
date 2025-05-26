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
            InitMatrix(&Ai->Weights[i], Ai->Hiddenlayer_Neuron_Number[i + 1],
                       (i == 0) ? Ai->input_Number : Ai->Hiddenlayer_Neuron_Number[i]);
        }
    Ai->Biases = malloc((Ai->Hiddenlayer_Number + 1) * sizeof(Vector));
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        InitVector(&Ai->Biases[i], Ai->Hiddenlayer_Neuron_Number[i]);
    }
}

void FreeAI(AI* Ai) {
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        FreeMatrix(&Ai->Weights[i]);
        FreeVector(&Ai->Biases[i]);
    }
    free(Ai->Weights);
    free(Ai->Biases);
}

void SetWeights(AI* Ai, Matrix matrix, int Weight_Number) {
    if (Weight_Number > Ai->Hiddenlayer_Number) {
        printf("Weight_Number > Ai->Hiddenlayer_Number\nError in SetWeights");
        exit(EXIT_FAILURE);
    }
    Ai->Weights[Weight_Number] = matrix;
}

void SetBiases(AI* Ai, Vector vector, int Bias_Number) {
    if (Ai->Hiddenlayer_Number != Bias_Number) {
        printf("Error in SetBiases\n");
        exit(EXIT_FAILURE);
    }
    Ai->Biases[Bias_Number] = vector;
}

double Sigmoid(float x) {
    return 1.0 / (1.0 + expf(-x));
}

Vector Forward(AI* Ai, Vector input) {
    if (Ai->input_Number != input.length) {
        printf("Error in Forward\nInput Vector length > Ai input number");
        exit(EXIT_FAILURE);
    }
    Vector output;
    InitVector(&output, Ai->output_Number);
    for (int i = 0; i < Ai->Hiddenlayer_Number; i++) {

    }
    return output;
}