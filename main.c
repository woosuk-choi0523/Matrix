#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>   // For srand
#include <math.h>   // For powf (used in MSE calculation)

#include "Matrix.h" // Defines Matrix, Vector, and their operations
#include "Ai.h"     // Defines AI structure, InitAI, FreeAI, Forward, BackPropagation, Sigmoid, Sigmoid_prime

int main() {
    // Seed the random number generator (used in InitAI if RandInit is true)


    // 1. Define Network Parameters
    int input_size = 2;
    int output_size = 1;
    int num_hidden_layers = 1;
    int hidden_layer_neuron_numbers[] = {3}; // One hidden layer with 3 neurons

    // 2. Initialize AI model
    AI model;
    // Assuming Sigmoid and Sigmoid_prime are accessible (e.g., defined in Ai.c)
    InitAI(&model, input_size, output_size, num_hidden_layers, hidden_layer_neuron_numbers, Sigmoid, Sigmoid_prime, true); // true for random initialization

    printf("AI Model Initialized:\n");
    printf("Input Size: %d\n", model.input_Number);
    printf("Output Size: %d\n", model.output_Number);
    printf("Hidden Layers: %d\n", model.Hiddenlayer_Number);
    if (model.Hiddenlayer_Number > 0) {
        for (int i = 0; i < model.Hiddenlayer_Number; i++) {
            printf("Neurons in Hidden Layer %d: %d\n", i + 1, model.Hiddenlayer_Neuron_Number[i]);
        }
    }
    printf("Weights[0] dimensions: %d x %d\n", model.Weights[0].rows, model.Weights[0].cols);
     if (num_hidden_layers > 0) { // Weight matrix between last hidden layer and output
        printf("Weights[1] dimensions: %d x %d\n", model.Weights[num_hidden_layers].rows, model.Weights[num_hidden_layers].cols);
     }


    // 3. Create Sample Training Data (single instance)
    Vector training_input;
    InitVector(&training_input, input_size);
    training_input.Vector[0] = 0.1f;
    training_input.Vector[1] = 0.9f;

    Vector training_target;
    InitVector(&training_target, output_size);
    training_target.Vector[0] = 0.5f;

    printf("\nTraining with Input: [%f, %f], Target: [%f]\n\n", training_input.Vector[0], training_input.Vector[1], training_target.Vector[0]);

    // 4. Training Loop
    float learning_rate = 0.1f;
    int epochs = 100; // Number of training iterations

    for (int epoch = 0; epoch < epochs; epoch++) {
        // Perform a forward pass to get current prediction for loss calculation
        Vector prediction = Forward(&model, training_input); //

        // Calculate Mean Squared Error (MSE)
        float mse = 0.0f;
        if (prediction.length == training_target.length) {
            for (int k = 0; k < prediction.length; k++) {
                mse += powf(prediction.Vector[k] - training_target.Vector[k], 2.0f);
            }
            mse /= prediction.length;
        } else {
            printf("Epoch %d: Error - Prediction and target length mismatch for MSE calculation.\n", epoch);
            FreeVector(&prediction);
            break;
        }

        if (epoch % 10 == 0 || epoch == epochs -1) { // Print MSE every 10 epochs and for the last one
             printf("Epoch %d/%d, MSE: %f, Prediction: [", epoch + 1, epochs, mse);
             for(int k=0; k < prediction.length; ++k) {
                 printf("%f%s", prediction.Vector[k], (k == prediction.length - 1) ? "" : ", ");
             }
             printf("]\n");
        }
        FreeVector(&prediction);


        // Call BackPropagation to get gradients
        // Ensure BackPropagation function signature is: AI BackPropagation(AI *ai, Vector input, Vector target_output)
        AI gradients = BackPropagation(&model, training_input, training_target);

        // Update Weights and Biases
        for (int l = 0; l <= model.Hiddenlayer_Number; l++) { // Iterate through all layers (input-hidden, hidden-hidden, hidden-output)
            // Update Biases: B = B - learning_rate * dB
            for (int j = 0; j < model.Biases[l].length; j++) {
                model.Biases[l].Vector[j] -= learning_rate * gradients.Biases[l].Vector[j];
            }

            // Update Weights: W = W - learning_rate * dW
            // Matrix elements are stored in a 1D array
            for (int j = 0; j < model.Weights[l].rows * model.Weights[l].cols; j++) {
                model.Weights[l].Matrix[j] -= learning_rate * gradients.Weights[l].Matrix[j];
            }
        }

        // Free the gradient AI structure
        FreeAI(&gradients); //
    }

    printf("\nTraining Finished.\n");

    // 5. Test After Training (Optional)
    Vector final_prediction = Forward(&model, training_input);
    printf("Final Prediction for Input: [%f, %f] -> Target: [%f], Got: [", training_input.Vector[0], training_input.Vector[1], training_target.Vector[0]);
    for(int k=0; k < final_prediction.length; ++k) {
        printf("%f%s", final_prediction.Vector[k], (k == final_prediction.length - 1) ? "" : ", ");
    }
    printf("]\n");
    FreeVector(&final_prediction);


    // 6. Free Memory
    FreeAI(&model);
    FreeVector(&training_input);
    FreeVector(&training_target);

    printf("\nAll memory freed. Exiting.\n");

    return 0;
}