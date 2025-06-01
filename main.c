#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Ai.h"


int main() {
    AI Ai;
    int Hidden_Layer_Neuron_Number[] = {1024, 512, 256};
    InitAI(&Ai,1048576, 50,3, Hidden_Layer_Neuron_Number,Sigmoid,Sigmoid_prime, true);
}