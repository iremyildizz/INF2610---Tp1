/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part2.c
 *
 * Ajoutez vos noms, prénoms et matricules
 * Irem Yildiz 2125282
 * Pablo Cabale Guerra 2129466
*/
#include "challenges_part2.h"

short** allocateMatrix(short rows, short cols) {
    short** matrix = malloc(rows * sizeof(short*));

    for (short i = 0; i < rows; i++)
        matrix[i] = calloc(cols, sizeof(short));

    return matrix;
}

void releaseMatrix(short** matrix, short rows) {
    for (short i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}

void printMatrix(Matrix* matrix) {
    printf("Matrice (%d x %d):\n", matrix->rows, matrix->cols);

    for (short i = 0; i < matrix->rows; i++) {
        for (short j = 0; j < matrix->cols; j++)
            printf("%d\t", matrix->matrix[i][j]);

        printf("\n");
    }
}

Matrix* multiply(Matrix* A, Matrix* B) {
    if (A == NULL || B == NULL)
        return NULL;

    if (A->cols != B->rows)
        return NULL;

    Matrix* C = malloc(sizeof(Matrix));
    
    C->rows = A->rows;
    C->cols = B->cols;
    C->matrix = allocateMatrix(C->rows, C->cols);

    for (short i = 0; i < A->rows; i++) {
        for (short j = 0; j < B->cols; j++) {
            short sum = 0;
            for (short k = 0; k < A->cols; k++) {
                sum += A->matrix[i][k] * B->matrix[k][j];
            }
            C->matrix[i][j] = sum;
        }
    }

    return C;
}


// This main is to help you in your development. 
// Don't forget to comment it out when you run the tests.
// int main(int argc, char*argv[])
// {
//     Matrix A;
//     A.rows = 2;
//     A.cols = 3;
//     A.matrix = allocateMatrix(A.rows, A.cols);

//     A.matrix[0][0] = 1;
//     A.matrix[0][1] = 2;
//     A.matrix[0][2] = 3;
//     A.matrix[1][0] = 4;
//     A.matrix[1][1] = 5;
//     A.matrix[1][2] = 6;
//     printMatrix(&A);

//     Matrix B;
//     B.rows = 3;
//     B.cols = 2;
//     B.matrix = allocateMatrix(B.rows, B.cols);

//     B.matrix[0][0] = 7;
//     B.matrix[0][1] = 8;
//     B.matrix[1][0] = 9;
//     B.matrix[1][1] = 10;
//     B.matrix[2][0] = 11;
//     B.matrix[2][1] = 12;
//     printMatrix(&B);

//     Matrix* C = multiply(&A, &B);
//     printMatrix(C);

//     releaseMatrix(A.matrix, A.rows);
//     releaseMatrix(B.matrix, B.rows);
//     releaseMatrix(C->matrix, C->rows);
//     free(C);

//     return 0;
// }
