#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations

int** mat_clone(int** mat, int col, int rows){
    //allocate for the clone matrix head
    int** clone = malloc(rows * sizeof(int*));
    //using the size params, malloc for the rows
    for (int i = 0; i < rows; i++){
        clone[i] = malloc(col * sizeof(int));
        for (int j = 0; j < cols; j++) {
            clone[i][j] = matrix[i][j];
        }
    }
    return clone
}

void add_mats(int** matrix1, int** matrix2, int rows, int cols, int** result_matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result_matrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void sub_mats(int** matrix1, int** matrix2, int rows, int cols, int** result_matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result_matrix[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

int* vec_clone(int* vec, int length){
    //allocate for the clone vector
    int* clone = malloc(length * sizeof(int));
    //using the size params, copy the data
    for (int i = 0; i < length; i++){
        clone[i] = vec[i];
    }
    return clone
}

void add_vecs(int* vec1, int* vec2, int size, int* result_vec) {
    for (int i = 0; i < size; i++) {
        result_vec[i] = vec1[i] + vec2[i];
    }
}

void sub_vecs(int* vec1, int* vec2, int size, int* result_vec) {
    for (int i = 0; i < size; i++) {
        result_vec[i] = vec1[i] - vec2[i];
    }
}
