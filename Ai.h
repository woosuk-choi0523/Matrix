#ifndef AI_H
#define AI_H

typedef struct{
    int input_Number;
    int Hiddenlayer_Number;
    int* Hiddenlayer_Neuron_Number;
    int output_Number;
    Matrix* Weights;
    Vector* Biases;
}AI;

void InitAI(AI* Ai, int input_Number, int Hiddenlayer_Number ,int* Hiddenlayer_Neuron_Number, int output_Number);

void FreeAI(AI* Ai);

void SetWeights(AI* Ai, Matrix matrix, int Weight_Number);

void SetBiases(AI* Ai, Matrix matrix, int Bias_Number);

double Sigmoid(float x);

Vector Forward(AI* Ai, Vector input);

#endif //AI_H
