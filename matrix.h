/* Please DO NOT modify this file */

#ifndef __MATRIX__H__
#define __MATRIX__H__

/* Structrue of a matrix */
typedef struct Matrix {
    unsigned int nrows;     /* number of rows in the matrix */
    unsigned int ncols;     /* number of cols in the matrix */
    int **data;             /* array of int pointers. each pointer points to an array of int. (to store 2-d matrix) */
} TMatrix;

/* Struct of thread argument */
typedef struct {
    int num_threads;        /* total number of threads participating in the computation */
    unsigned int id;        /* int id of a thread. Ranges between 0 to num_threads-1 */
    TMatrix *m, *n, *t;     /* pointers to input matrices m and n and output matrix t */
} thread_arg_t;

TMatrix * newMatrix(unsigned int nrows, unsigned int ncols);
void freeMatrix(TMatrix * m);
TMatrix * fillMatrix(TMatrix * m);
void printMatrix(TMatrix * m);
int compareMatrix(TMatrix * m, TMatrix *n);
TMatrix * addMatrix(TMatrix * m, TMatrix * n);
TMatrix * addMatrix_thread(int nbT, TMatrix * m, TMatrix * n);


#endif
