//
// Created by woosu on 25. 5. 25.
//

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

#endif //AI_H
