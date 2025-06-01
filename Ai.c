#include "Matrix.h"
#include "Ai.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void InitAI(AI* Ai, int input_Number, int output_Number, int Hiddenlayer_Number ,int* Hiddenlayer_Neuron_Number, float (*ActivationFunction)(float), float (*ActivationFunction_prime)(float), bool RandInit) {
    Ai->Hiddenlayer_Neuron_Number = Hiddenlayer_Neuron_Number;
    Ai->Hiddenlayer_Number = Hiddenlayer_Number;
    Ai->input_Number = input_Number;
    Ai->output_Number = output_Number;
    Ai->ActivationFunction = ActivationFunction;
    Ai->ActivationFunction_prime = ActivationFunction_prime;
    Ai->Weights = malloc((Ai->Hiddenlayer_Number + 1) * sizeof(Matrix));
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        if (i == 0) {
            InitMatrix(&Ai->Weights[0], Hiddenlayer_Neuron_Number[0], input_Number);
        }else if (i == Ai->Hiddenlayer_Number) {
            InitMatrix(&Ai->Weights[Hiddenlayer_Number], output_Number, Hiddenlayer_Neuron_Number[Hiddenlayer_Number - 1]);
        }else {
            InitMatrix(&Ai->Weights[i],Hiddenlayer_Neuron_Number[i],Hiddenlayer_Neuron_Number[i - 1]);
        }
        if (RandInit) RandomMatrix(&Ai->Weights[i]);

        }
    Ai->Biases = malloc((Ai->Hiddenlayer_Number + 1) * sizeof(Vector));
    for (int i = 0; i < Ai->Hiddenlayer_Number + 1; i++) {
        if (i == Hiddenlayer_Number) {
            InitVector(&Ai->Biases[i], output_Number);
        }else {
            InitVector(&Ai->Biases[i], Ai->Hiddenlayer_Neuron_Number[i]);
        }
        if (RandInit) RandomVector(&Ai->Biases[i]);

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

float uniform_random(float min_val, float max_val) {
    if (min_val >= max_val) {
        // 오류 처리 또는 min_val 반환
        return min_val;
    }
    return min_val + ((float)rand() / RAND_MAX) * (max_val - min_val);
}

void RandomMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->cols * matrix->rows; i++) {
        matrix->Matrix[i] = uniform_random(-0.1, 0.1);
    }
}

void RandomVector(Vector *vector) {
    for (int i =0; i < vector->length; i++) {
        vector->Vector[i] = uniform_random(-0.1, 0.1);
    }
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

float Sigmoid(float x) {
    return 1.0 / (expf(-x) + 1.0);
}

float Sigmoid_prime(float x) {
    return Sigmoid(x) * Sigmoid(x);
}

Vector VectorFunc(Vector vector, float(*func)(float)) {
    Vector result;
    InitVector(&result,vector.length);
    for (int i = 0; i < vector.length; i++) {
        result.Vector[i] = func(vector.Vector[i]);
    }
    return result;
}

Vector Forward(AI* Ai, Vector input) {
    if (Ai->input_Number != input.length) {
        printf("Error in Forward\nInput Vector length > Ai input number");
        exit(EXIT_FAILURE);
    }
    Vector output;
    InitVector(&output,input.length);
    Vector temp;
    for (int i = 0; i < Ai->Hiddenlayer_Number; i++) {
        temp = output;
        output = MultiplyMatrix(Ai->Weights[i],i == 0 ? input : output);
        FreeVector(&temp);
        temp = output;
        output = VectorFunc(output, Ai->ActivationFunction);
        FreeVector(&temp);
    }
    return output;
}

AI BackPropagation(AI *ai, Vector input) {
    AI output;
    InitAI(&output, ai->input_Number, ai->Hiddenlayer_Number, ai->Hiddenlayer_Neuron_Number, ai->output_Number,ai->ActivationFunction, ai->ActivationFunction_prime, false);
    if (ai->input_Number != input.length) {
        printf("Error in BackPropagation\nInput Vector length > Ai input number");
        exit(EXIT_FAILURE);
    }
    Vector *LayerOutput = malloc((ai->Hiddenlayer_Number + 1) * sizeof(Vector));
    Vector *RawLayerOutput = malloc((ai->Hiddenlayer_Number + 1) * sizeof(Vector));
    for (int i = 0; i < ai->Hiddenlayer_Number + 1; i++) {
        InitVector(&LayerOutput[i], ai->Hiddenlayer_Neuron_Number[i]);
        InitVector(&RawLayerOutput[i], ai->Hiddenlayer_Neuron_Number[i]);
    }
    for (int i = 0; i < ai->Hiddenlayer_Number + 1; i++) {
        if (i == 0) {
            LayerOutput[i] = MultiplyMatrix(ai->Weights[i], input);
        }else {
            LayerOutput[i] = MultiplyMatrix(ai->Weights[i], VectorFunc(LayerOutput[i - 1], ai->ActivationFunction));
        }
    }

    for (int i = 0; i < ai->Hiddenlayer_Number; i++) {
        FreeVector(&LayerOutput[i]);
        FreeVector(&RawLayerOutput[i]);
    }
    free(LayerOutput);
    free(RawLayerOutput);
    return output;
}