#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <stdlib.h>

void copyArray(size_t, double*, double**);
double* allocForArrayDouble(const size_t);
void freeArrayDouble(double*);

#endif // ARRAYUTILS_H
