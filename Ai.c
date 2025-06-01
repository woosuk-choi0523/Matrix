#include "Matrix.h"
#include "Ai.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

void InitAI(AI* Ai, int input_Number, int output_Number, int Hiddenlayer_Number ,int* Hiddenlayer_Neuron_Number, float (*ActivationFunction)(float), float (*ActivationFunction_prime)(float), bool RandInit) {
    srand(time(NULL));
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
        printf("Error in Forward: Input vector length (%d) does not match AI input number (%d).\n", input.length, Ai->input_Number);
        exit(EXIT_FAILURE);
    }

    Vector output;
    // This initial vector's memory is managed by the temp/free pattern within the loop.
    // Its initial size doesn't determine the final output size.
    InitVector(&output, input.length);
    Vector temp;

    // Corrected loop: iterates Ai->Hiddenlayer_Number + 1 times
    // This ensures all layers, including the one to the output layer, are processed.
    for (int i = 0; i < (Ai->Hiddenlayer_Number + 1); i++) {
        temp = output; // Store the current 'output' vector (which is A_prev from the previous layer, or the initial allocation for i=0)

        // Calculate Z = W * A_prev
        // (i == 0 ? input : output) correctly selects the input to the current layer
        Vector z_val = MultiplyMatrix(Ai->Weights[i], (i == 0 ? input : output));

        // Add Bias: Z_biased = Z + B (IMPORTANT CORRECTION)
        Vector z_biased = AddVector(z_val, Ai->Biases[i]);
        FreeVector(&z_val); // Free the vector returned by MultiplyMatrix

        // Free the vector that was stored in 'temp'.
        // For i=0, this frees the initial vector created by InitVector(&output, input.length).
        // For i>0, this frees the activation vector (A_prev) from the previous layer.
        FreeVector(&temp);

        // Activate: A_curr = g(Z_biased)
        temp = z_biased; // Store z_biased before VectorFunc might consume/alter it (depending on VectorFunc impl.)
        output = VectorFunc(z_biased, Ai->ActivationFunction); // 'output' is now the new activation A_curr
        FreeVector(&temp); // Free z_biased
    }

    // 'output' now holds the final activated output of the network
    return output;
}


AI BackPropagation(AI *ai, Vector input, Vector target_output) {
    AI delta_ai; // This AI will store the gradients (nabla_W, nabla_B)
    // Initialize delta_ai with the same architecture as ai, with weights/biases set to 0
    InitAI(&delta_ai, ai->input_Number, ai->output_Number, ai->Hiddenlayer_Number,
           ai->Hiddenlayer_Neuron_Number, ai->ActivationFunction,
           ai->ActivationFunction_prime, false); // false for RandInit to get zero matrices/vectors

    if (ai->input_Number != input.length) {
        printf("Error in BackPropagation: Input vector length (%d) does not match AI input number (%d).\n", input.length, ai->input_Number);
        exit(EXIT_FAILURE);
    }
    if (ai->output_Number != target_output.length) {
        printf("Error in BackPropagation: Target output vector length (%d) does not match AI output number (%d).\n", target_output.length, ai->output_Number);
        exit(EXIT_FAILURE);
    }

    int num_weight_sets = ai->Hiddenlayer_Number + 1;

    // --- Forward Pass: Store all Z (raw outputs) and A (activations) ---
    Vector *zs = malloc(num_weight_sets * sizeof(Vector));       // Z values for each layer (pre-activation)
    Vector *as = malloc((num_weight_sets + 1) * sizeof(Vector)); // Activations for each layer (a[0] is input)

    as[0] = CopyVector(input); // a[0] = input layer activation

    for (int l = 0; l < num_weight_sets; l++) {
        Vector prev_a = as[l];
        Vector Z_l_temp = MultiplyMatrix(ai->Weights[l], prev_a); // W * a_prev

        // Correctly initialize zs[l] before assignment if AddVector modifies in place,
        // or ensure AddVector returns a new vector. Assuming AddVector returns new.
        Vector Z_l_biased = AddVector(Z_l_temp, ai->Biases[l]);      // Z = W * a_prev + B
        zs[l] = Z_l_biased; // Store Z for layer l+1 (using 0-indexed weights/biases)
        FreeVector(&Z_l_temp);

        as[l+1] = VectorFunc(zs[l], ai->ActivationFunction); // a = g(Z)
    }

    // --- Backward Pass: Calculate deltas (error terms) ---
    Vector *deltas = malloc(num_weight_sets * sizeof(Vector)); // delta values for each layer's output

    // Calculate delta for the output layer
    // delta_L = (a_L - y) * g'(Z_L)
    Vector cost_derivative_output = SubtractVector(as[num_weight_sets], target_output); // (a_L - y)
    Vector sp_L = VectorFunc(zs[num_weight_sets - 1], ai->ActivationFunction_prime); // g'(Z_L)
    deltas[num_weight_sets - 1] = ElementWiseMultiplyVector(cost_derivative_output, sp_L);
    FreeVector(&cost_derivative_output);
    FreeVector(&sp_L);

    // Calculate deltas for hidden layers (from L-1 down to 1)
    // delta_l = ( (W_{l+1})^T * delta_{l+1} ) * g'(Z_l)
    for (int l = num_weight_sets - 2; l >= 0; l--) {
        Matrix W_next_T = TransposeMatrix(ai->Weights[l+1]);
        Vector propagated_error = MultiplyMatrix_Vec(W_next_T, deltas[l+1]); // (W_{l+1})^T * delta_{l+1}

        Vector sp_l = VectorFunc(zs[l], ai->ActivationFunction_prime); // g'(Z_l)
        deltas[l] = ElementWiseMultiplyVector(propagated_error, sp_l);

        FreeMatrix(&W_next_T);
        FreeVector(&propagated_error);
        FreeVector(&sp_l);
    }

    // --- Calculate Gradients for Weights and Biases ---
    // nabla_B_l = delta_l
    // nabla_W_l = delta_l * (a_{l-1})^T
    for (int l = 0; l < num_weight_sets; l++) {
        // Gradient for biases (delta_ai.Biases[l] was initialized to zero vector)
        FreeVector(&delta_ai.Biases[l]); // Free the zero vector
        delta_ai.Biases[l] = CopyVector(deltas[l]);

        // Gradient for weights (delta_ai.Weights[l] was initialized to zero matrix)
        Vector prev_a_for_grad = as[l]; // This is a_{l-1} in standard notation (activation input to current layer l)
        Matrix dW = OuterProduct(deltas[l], prev_a_for_grad);

        FreeMatrix(&delta_ai.Weights[l]); // Free the zero matrix
        delta_ai.Weights[l] = dW;
    }

    // --- Cleanup ---
    FreeVector(&as[0]); // Free the copied input activation
    for (int l = 0; l < num_weight_sets; l++) {
        FreeVector(&zs[l]);
        FreeVector(&as[l+1]); // as[0] already freed, as[num_weight_sets] is the last one
        FreeVector(&deltas[l]);
    }
    free(zs);
    free(as);
    free(deltas);

    return delta_ai;
}