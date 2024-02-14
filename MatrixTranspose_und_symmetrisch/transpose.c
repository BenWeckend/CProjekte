#include <stdbool.h>
#include "header.h"

int transpose(int matrix[MATRIX_SIZE][MATRIX_SIZE], int transMatrix[MATRIX_SIZE][MATRIX_SIZE], int n){
    for(int i=0; i<n; i++){
        for(int y=0; y<n; y++){
            transMatrix[y][i] = matrix[i][y];
        }
    }
}

bool istSymmetrisch(int matrix[MATRIX_SIZE][MATRIX_SIZE], int n){
    bool istGleich;
    int transMatrix[MATRIX_SIZE][MATRIX_SIZE];

    transpose(matrix, transMatrix, n);

    for(int i=0; i<n; i++){
        for(int y=0; y<n; y++){
            if(transMatrix[i][y] != matrix[i][y]){
                return istGleich = false;
            }
        }
    }
    return true;
}