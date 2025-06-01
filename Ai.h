#ifndef AI_H
#define AI_H
#include <stdbool.h>

typedef struct{
    int input_Number;
    int Hiddenlayer_Number;
    int* Hiddenlayer_Neuron_Number;
    int output_Number;
    Matrix* Weights;
    Vector* Biases;
    float (*ActivationFunction)(float);
    float (*ActivationFunction_prime)(float);
}AI;

void InitAI(AI* Ai, int input_Number, int output_Number, int Hiddenlayer_Number ,int* Hiddenlayer_Neuron_Number, float (*ActivationFunction)(float), float (*ActivationFunction_prime)(float),bool RandInit);

void FreeAI(AI* Ai);

float uniform_random(float min_val, float max_val);

void RandomMatrix(Matrix* matrix);

void RandomVector(Vector* vector);

void SetWeights(AI* Ai, Matrix matrix, int Weight_Number);

void SetBiases(AI* Ai, Vector vector, int Bias_Number);

float Sigmoid(float x);

float Sigmoid_prime(float x);

Vector Forward(AI* Ai, Vector input);

#endif //AI_H
