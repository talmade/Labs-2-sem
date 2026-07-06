#include "arrayUtils.h"
#include <stdlib.h>

void copyArray(size_t sizeOrigArray, double* originalArray, double** copyArray) {
    *copyArray = allocForArrayDouble(sizeOrigArray);

    for (int i = 0; i < sizeOrigArray; ++i) {
        (*copyArray)[i] = originalArray[i];
    }
}

double* allocForArrayDouble(const size_t size) {return (double*) malloc(size * sizeof(double));}

void freeArrayDouble(double* array) {free(array);}
