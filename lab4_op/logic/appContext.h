#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "statusCode.h"

#define SIZE_MATRIX 4

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

typedef struct {
    double data[SIZE_MATRIX][SIZE_MATRIX];
} Matrix4x4;

typedef struct {
    double** data;
    int rows;
    int columns;
    double minValue;
    double maxValue;
} DataModel;

typedef struct {
    Point3D* normalizedPoints;
    Point3D* transformedPoints;
    int rows;
    int columns;
    double normMin;
    double normMax;
    double step;
} SceneData;

typedef struct {
    double rotateX;
    double rotateY;
    double rotateZ;
    double translateX;
    double translateY;
    double translateZ;
    double scale;
} TransformParams;

typedef struct {
    DataModel rawModel;
    SceneData scene;
    TransformParams transform;
    char* errorMessage;
    char* filename;
    Status status;
} AppContext;

#endif // APPCONTEXT_H
