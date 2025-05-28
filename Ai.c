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

// ---
// ## save_ai_to_file: AI 구조체를 이진 파일로 저장
//
// filename: 저장할 파일의 이름
// ai: 저장할 AI 구조체의 포인터
//
// 반환값: 0 (성공), 1 (파일 열기 실패), 2 (쓰기 실패)
// ---
int save_ai_to_file(const char *filename, const AI *ai) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("파일 쓰기 오류");
        return 1;
    }

    // 1. 고정된 크기의 멤버 저장
    if (fwrite(&ai->input_Number, sizeof(int), 1, fp) != 1 ||
        fwrite(&ai->Hiddenlayer_Number, sizeof(int), 1, fp) != 1 ||
        fwrite(&ai->output_Number, sizeof(int), 1, fp) != 1) {
        perror("AI 기본 정보 쓰기 오류");
        fclose(fp);
        return 2;
    }

    // 2. Hiddenlayer_Neuron_Number 배열 저장
    if (ai->Hiddenlayer_Number > 0) {
        if (fwrite(ai->Hiddenlayer_Neuron_Number, sizeof(int), ai->Hiddenlayer_Number, fp) != ai->Hiddenlayer_Number) {
            perror("Hiddenlayer_Neuron_Number 쓰기 오류");
            fclose(fp);
            return 2;
        }
    }

    // 3. Weights 배열 저장 (Hiddenlayer_Number + 1 개의 Matrix)
    int num_layers = ai->Hiddenlayer_Number + 1;
    for (int i = 0; i < num_layers; ++i) {
        // Matrix 메타데이터 (rows, cols) 저장
        if (fwrite(&ai->Weights[i].rows, sizeof(int), 1, fp) != 1 ||
            fwrite(&ai->Weights[i].cols, sizeof(int), 1, fp) != 1) {
            perror("Weights 메타데이터 쓰기 오류");
            fclose(fp);
            return 2;
        }
        // 실제 Matrix 데이터 저장
        size_t data_size = ai->Weights[i].rows * ai->Weights[i].cols;
        if (fwrite(ai->Weights[i].data, sizeof(double), data_size, fp) != data_size) {
            perror("Weights 데이터 쓰기 오류");
            fclose(fp);
            return 2;
        }
    }

    // 4. Biases 배열 저장 (Hiddenlayer_Number + 1 개의 Vector)
    for (int i = 0; i < num_layers; ++i) {
        // Vector 메타데이터 (size) 저장
        if (fwrite(&ai->Biases[i].size, sizeof(int), 1, fp) != 1) {
            perror("Biases 메타데이터 쓰기 오류");
            fclose(fp);
            return 2;
        }
        // 실제 Vector 데이터 저장
        size_t data_size = ai->Biases[i].size;
        if (fwrite(ai->Biases[i].data, sizeof(double), data_size, fp) != data_size) {
            perror("Biases 데이터 쓰기 오류");
            fclose(fp);
            return 2;
        }
    }

    fclose(fp);
    return 0;
}

// ---
// ## load_ai_from_file: 이진 파일에서 AI 구조체를 불러오기
//
// filename: 불러올 파일의 이름
//
// 반환값: 불러온 AI 구조체의 포인터 (실패 시 NULL)
//         *반환된 AI 구조체는 호출자가 반드시 FreeAI()로 해제해야 함.*
// ---
AI* load_ai_from_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("파일 읽기 오류");
        return NULL;
    }

    AI* ai = (AI*)malloc(sizeof(AI));
    if (!ai) {
        perror("AI 구조체 메모리 할당 오류");
        fclose(fp);
        return NULL;
    }
    // 초기화 (오류 발생 시 FreeAI에서 문제 없도록)
    ai->Hiddenlayer_Neuron_Number = NULL;
    ai->Weights = NULL;
    ai->Biases = NULL;

    // 1. 고정된 크기의 멤버 읽기
    if (fread(&ai->input_Number, sizeof(int), 1, fp) != 1 ||
        fread(&ai->Hiddenlayer_Number, sizeof(int), 1, fp) != 1 ||
        fread(&ai->output_Number, sizeof(int), 1, fp) != 1) {
        perror("AI 기본 정보 읽기 오류");
        FreeAI(ai); // 부분적으로 할당된 메모리 해제
        fclose(fp);
        return NULL;
    }

    // 2. Hiddenlayer_Neuron_Number 배열 읽기
    if (ai->Hiddenlayer_Number > 0) {
        ai->Hiddenlayer_Neuron_Number = (int*)malloc(sizeof(int) * ai->Hiddenlayer_Number);
        if (!ai->Hiddenlayer_Neuron_Number) {
            perror("Hiddenlayer_Neuron_Number 메모리 할당 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
        if (fread(ai->Hiddenlayer_Neuron_Number, sizeof(int), ai->Hiddenlayer_Number, fp) != ai->Hiddenlayer_Number) {
            perror("Hiddenlayer_Neuron_Number 읽기 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
    } else {
        ai->Hiddenlayer_Neuron_Number = NULL; // 히든 레이어가 없으면 NULL로 설정
    }

    // 3. Weights 배열 읽기 (Hiddenlayer_Number + 1 개의 Matrix)
    int num_layers = ai->Hiddenlayer_Number + 1;
    ai->Weights = (Matrix*)malloc(sizeof(Matrix) * num_layers);
    if (!ai->Weights) {
        perror("Weights 배열 메모리 할당 오류");
        FreeAI(ai);
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < num_layers; ++i) {
        // Matrix 메타데이터 (rows, cols) 읽기
        if (fread(&ai->Weights[i].rows, sizeof(int), 1, fp) != 1 ||
            fread(&ai->Weights[i].cols, sizeof(int), 1, fp) != 1) {
            perror("Weights 메타데이터 읽기 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
        // 실제 Matrix 데이터 메모리 할당 및 읽기
        size_t data_size = ai->Weights[i].rows * ai->Weights[i].cols;
        ai->Weights[i].data = (double*)malloc(sizeof(double) * data_size);
        if (!ai->Weights[i].data) {
            perror("Weights 데이터 메모리 할당 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
        if (fread(ai->Weights[i].data, sizeof(double), data_size, fp) != data_size) {
            perror("Weights 데이터 읽기 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
    }

    // 4. Biases 배열 읽기 (Hiddenlayer_Number + 1 개의 Vector)
    ai->Biases = (Vector*)malloc(sizeof(Vector) * num_layers);
    if (!ai->Biases) {
        perror("Biases 배열 메모리 할당 오류");
        FreeAI(ai);
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < num_layers; ++i) {
        // Vector 메타데이터 (size) 읽기
        if (fread(&ai->Biases[i].size, sizeof(int), 1, fp) != 1) {
            perror("Biases 메타데이터 읽기 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
        // 실제 Vector 데이터 메모리 할당 및 읽기
        size_t data_size = ai->Biases[i].size;
        ai->Biases[i].data = (double*)malloc(sizeof(double) * data_size);
        if (!ai->Biases[i].data) {
            perror("Biases 데이터 메모리 할당 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
        if (fread(ai->Biases[i].data, sizeof(double), data_size, fp) != data_size) {
            perror("Biases 데이터 읽기 오류");
            FreeAI(ai);
            fclose(fp);
            return NULL;
        }
    }

    fclose(fp);
    return ai;
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

void VectorFunc(Vector *vector, float(*func)(float)) {
    for (int i = 0; i < vector->length; i++) {
        vector->Vector[i] = func(vector->Vector[i]);
    }
}

Vector Forward(AI* Ai, Vector input) {
    if (Ai->input_Number != input.length) {
        printf("Error in Forward\nInput Vector length > Ai input number");
        exit(EXIT_FAILURE);
    }
    Vector output;
    Vector temp;
    for (int i = 0; i < Ai->Hiddenlayer_Number; i++) {
        temp = output;
        output = MultiplyMatrix(Ai->Weights[i],i == 0 ? input : output);
        FreeVector(&temp);
        VectorFunc(&output, Sigmoid);
    }
    return output;
}

