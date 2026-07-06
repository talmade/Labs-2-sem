#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include "appContext.h"

double** allocMatrix(int rows, int cols);
void freeMatrix(double** matrix, int rows);
Point3D* allocPoints(int count);
void freePoints(Point3D** points);

#endif // MATRIXUTILS_H
