#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "matrix.h"

/* Creates and returns a matrix of size nrows x ncols */
TMatrix *newMatrix(unsigned int nrows, unsigned int ncols) {
    if (!nrows || !ncols) 
        return NULL;

    TMatrix* newM = malloc(sizeof(TMatrix));
    int** data = malloc(nrows * sizeof(int*));
    int* storage = malloc(nrows * ncols * sizeof(int));

    if (newM == NULL || data == NULL || storage == NULL) {
        free(newM);
        free(data);
        free(storage);
        return NULL;
    }

    for (size_t i = 0; i < nrows; i++)
        data[i] = storage + i * ncols;

    newM->nrows = nrows;
    newM->ncols = ncols;
    newM->data = data;

    return newM;
}

/* Deallocates the dynamic memory used by a matrix */
void freeMatrix(TMatrix *m) {
    if (m == NULL) return;
    if (m->data) {
        free(m->data[0]);
        free(m->data);
    }
    free(m);
}

/* Fill the matrix with random int values */
TMatrix *fillMatrix(TMatrix *m) {
    if (m == NULL || m->data == NULL) 
        return m;

    srand(3100);
    for (unsigned int i = 0; i < m->nrows; i++)
        for (unsigned int j = 0; j < m->ncols; j++)
            m->data[i][j] = rand() % 100;

    return m;
}

/* Prints the elements in a matrix */
void printMatrix(TMatrix *m) {
    if (m == NULL) return;

    for (unsigned int i = 0; i < m->nrows; i++) {
        for (unsigned int j = 0; j < m->ncols; j++)
            printf("%5d", m->data[i][j]);
        printf("\n");
    }
    printf("\n");
}

/* This function compares two matrices m and n */
int compareMatrix(TMatrix *m, TMatrix *n) {
    if (m == NULL || n == NULL) 
        return -1;

    for (unsigned i = 0; i < m->nrows; i++)
        for (unsigned j = 0; j < m->ncols; j++)
            if (m->data[i][j] != n->data[i][j]) {
                fprintf(stderr, "element[%u][%u] %d %d.\n", i, j, m->data[i][j], n->data[i][j]);
                return 1;
            }
    return 0;
}

/* Add two matrices m and n using a single thread */
TMatrix *addMatrix(TMatrix *m, TMatrix *n) {
    if (m == NULL || n == NULL || m->nrows != n->nrows || m->ncols != n->ncols)
        return NULL;

    TMatrix *t = newMatrix(m->nrows, m->ncols);
    if (t == NULL) return t;

    for (unsigned int i = 0; i < m->nrows; i++)
        for (unsigned int j = 0; j < m->ncols; j++)
            t->data[i][j] = m->data[i][j] + n->data[i][j];

    return t;
}

/* The function executed by the threads */
static void *thread_main(void *p_arg) {
    thread_arg_t *p = (thread_arg_t *)p_arg;
    unsigned int start_row = (p->id * p->m->nrows) / p->num_threads;
    unsigned int end_row = ((p->id + 1) * p->m->nrows) / p->num_threads;

    for (unsigned int i = start_row; i < end_row; i++) {
        for (unsigned int j = 0; j < p->m->ncols; j++) {
            p->t->data[i][j] = p->m->data[i][j] + p->n->data[i][j];
        }
    }
    return NULL;
}

/* Add two matrices m and n using nbT threads */
TMatrix *addMatrix_thread(int nbT, TMatrix *m, TMatrix *n) {
    if (m == NULL || n == NULL || m->nrows != n->nrows || m->ncols != n->ncols)
        return NULL;

    TMatrix *t = newMatrix(m->nrows, m->ncols);
    if (t == NULL) return t;

    pthread_t threads[nbT];
    thread_arg_t args[nbT];

    for (int i = 0; i < nbT; i++) {
        args[i].num_threads = nbT;
        args[i].id = i;
        args[i].m = m;
        args[i].n = n;
        args[i].t = t;
        pthread_create(&threads[i], NULL, thread_main, &args[i]);
    }

    for (int i = 0; i < nbT; i++) {
        pthread_join(threads[i], NULL);
    }

    return t;
}