#include <stdlib.h>
#include "matrixUtils.h"

double** allocMatrix(int rows, int cols) {
    double** matrix = (double**) malloc(rows * sizeof(double*));
    int i = 0;
    while (i < rows && matrix != NULL) {
        matrix[i] = (double*) malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            freeMatrix(matrix, i);
            matrix = NULL;
        }
        i++;
    }
    return matrix;
}

void freeMatrix(double** matrix, int rows) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++)
            free(matrix[i]);
        free(matrix);
    }
}

Point3D* allocPoints(int count) {
    return (Point3D*) malloc(count * sizeof(Point3D));
}

void freePoints(Point3D** points) {
    if (*points != NULL) {
        free(*points);
        *points = NULL;
    }
}
