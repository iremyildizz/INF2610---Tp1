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

typedef struct {
    Matrix* A;
    Matrix* B;
    Matrix* C;
    int startRow;
    int endRow;
} ThreadArgs;

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

void* multiplyThread(void* arguments) {
    ThreadArgs* args = (ThreadArgs*)arguments;
    Matrix* A = args->A;
    Matrix* B = args->B;
    Matrix* C = args->C;

    for (int i = args->startRow; i < args->endRow; i++) {
        for (int j = 0; j < B->cols; j++) {
            int sum = 0;
            for (int k = 0; k < A->cols; k++) {
                sum += (int)A->matrix[i][k] * (int)B->matrix[k][j];
            }
            C->matrix[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}

Matrix* multiply(Matrix* A, Matrix* B) {
    if (A == NULL || B == NULL)
        return NULL;

    if (A->rows == 0 || A->cols == 0 || B->rows == 0 || B->cols == 0)
        return NULL;

    if (A->cols != B->rows)
        return NULL;

    Matrix* C = malloc(sizeof(Matrix));
    
    C->rows = A->rows;
    C->cols = B->cols;
    C->matrix = allocateMatrix(C->rows, C->cols);

    long nbThreads = sysconf(_SC_NPROCESSORS_ONLN);
    if (nbThreads < 1)
        nbThreads = 1;

    if (nbThreads > C->rows)
        nbThreads = C->rows;
        
    pthread_t* tid = malloc(nbThreads * sizeof(pthread_t));
    ThreadArgs* args = malloc(nbThreads * sizeof(ThreadArgs));

    int rowsPerThread = C->rows / nbThreads;
    int remainingRows = C->rows % nbThreads;
    int currentRow = 0;

    for(long i = 0; i < nbThreads; i++) {
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        args[i].startRow = currentRow;
        args[i].endRow = currentRow + rowsPerThread + (i < remainingRows ? 1 : 0);;
        currentRow = args[i].endRow;

        pthread_create(&tid[i], NULL, multiplyThread, (void*) &args[i]);
    }

    for (int i = 0; i < nbThreads; i++)
        pthread_join(tid[i], NULL);

    free(tid);
    free(args);

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
