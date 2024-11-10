/* This is a test file to check the addition functionality.
 * Please DO NOT modify this file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "matrix.h"

int main(int argc, char ** argv) {
    if(argc < 3) {
        printf("The correct usage is: ./test nbT nrows ncols. \n");
        exit(-1);
    } 
    
    int nbT = atoi(argv[1]);        /* Number of threads */
    int nrows = atoi(argv[2]);      /* Number of rows */
    int ncols = atoi(argv[3]);      /* Number of columns */

    /* Create 2 matrices */
    TMatrix *m, *n;
    m = newMatrix(nrows, ncols);
    n = newMatrix(nrows, ncols);

    /* Fill the matrices m and n with random values */
    fillMatrix(m);
    fillMatrix(n);

    /* Add the matrices sequentially and then parallely. */
    TMatrix *t1, *t2;
    t1 = addMatrix(m, n);
    printMatrix(t1);
    t2 = addMatrix_thread(nbT, m, n);
    printMatrix(t2);

    /* Free the allocated memory */
    freeMatrix(m);
    freeMatrix(n);

    /* Compare the two matrices*/
    int r = compareMatrix(t1, t2);
    if (r) {
        printf("%s\n", "Results do not match.");
        exit(EXIT_FAILURE);
    } else {
        printf("%s\n", "Good work!");
    }

    return 0;
}

