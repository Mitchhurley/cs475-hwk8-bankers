#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations

int** mat_clone(int** mat, int col, int rows){
    //allocate for the clone matrix head
    int** clone = malloc(rows * sizeof(int));
    //using the size params, malloc for the rows
    for (int i = 0; i < rows; i++){
        clone[i] = malloc(col * sizeof(int));
        for (int j = 0; j < cols; j++) {
            clone[i][j] = matrix[i][j];
        }
    }
    return clone
}