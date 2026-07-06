#ifndef CALCULATEMETRIC_H
#define CALCULATEMETRIC_H

#include "AppContext.h"
#include "constants.h"

int getColumnOffset(const int*);
StatusCode calculateMetric(AppContext*, const ParamsUser*);
double* allocForArrayDouble(size_t);
void freeArrayDouble(double*);

#endif // CALCULATEMETRIC_H
