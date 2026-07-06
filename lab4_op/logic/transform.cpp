#include <math.h>
#include "transform.h"
#include "matrixUtils.h"

static void makeIdentity(Matrix4x4* matrix);
static void makeRotationX(Matrix4x4* matrix, double angle);
static void makeRotationY(Matrix4x4* matrix, double angle);
static void makeRotationZ(Matrix4x4* matrix, double angle);
static void makeScale(Matrix4x4* matrix, double scale);
static void multiplyMatrices(const Matrix4x4* a, const Matrix4x4* b, Matrix4x4* result);
static void multiplyMatrixPoint(const Matrix4x4* matrix, const Point3D* point, Point3D* result);
static void applyTranslation(const TransformParams* transform, Point3D* point);
static void buildTransformMatrix(const TransformParams* transform, Matrix4x4* result);

static void makeIdentity(Matrix4x4* matrix) {
    matrix->data[0][0] = 1.; matrix->data[0][1] = 0.; matrix->data[0][2] = 0.; matrix->data[0][3] = 0.;
    matrix->data[1][0] = 0.; matrix->data[1][1] = 1.; matrix->data[1][2] = 0.; matrix->data[1][3] = 0.;
    matrix->data[2][0] = 0.; matrix->data[2][1] = 0.; matrix->data[2][2] = 1.; matrix->data[2][3] = 0.;
    matrix->data[3][0] = 0.; matrix->data[3][1] = 0.; matrix->data[3][2] = 0.; matrix->data[3][3] = 1.;
}

static void makeScale(Matrix4x4* matrix, double scale) {
    makeIdentity(matrix);
    matrix->data[0][0] = scale;
    matrix->data[1][1] = scale;
    matrix->data[2][2] = scale;
}

static void makeRotationX(Matrix4x4* matrix, double angle) {
    makeIdentity(matrix);
    matrix->data[1][1] = cos(angle);
    matrix->data[1][2] = -sin(angle);
    matrix->data[2][1] = sin(angle);
    matrix->data[2][2] = cos(angle);
}

static void makeRotationY(Matrix4x4* matrix, double angle) {
    makeIdentity(matrix);
    matrix->data[0][0] = cos(angle);
    matrix->data[0][2] = sin(angle);
    matrix->data[2][0] = -sin(angle);
    matrix->data[2][2] = cos(angle);
}

static void makeRotationZ(Matrix4x4* matrix, double angle) {
    makeIdentity(matrix);
    matrix->data[0][0] = cos(angle);
    matrix->data[0][1] = -sin(angle);
    matrix->data[1][0] = sin(angle);
    matrix->data[1][1] = cos(angle);
}

static void multiplyMatrices(const Matrix4x4* a, const Matrix4x4* b, Matrix4x4* result) {
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++) {
            result->data[row][col] = 0.;
            for (int k = 0; k < 4; k++)
                result->data[row][col] += a->data[row][k] * b->data[k][col];
        }
}

static void multiplyMatrixPoint(const Matrix4x4* matrix, const Point3D* point, Point3D* result) {
    result->x = matrix->data[0][0]*point->x + matrix->data[0][1]*point->y + matrix->data[0][2]*point->z + matrix->data[0][3];
    result->y = matrix->data[1][0]*point->x + matrix->data[1][1]*point->y + matrix->data[1][2]*point->z + matrix->data[1][3];
    result->z = matrix->data[2][0]*point->x + matrix->data[2][1]*point->y + matrix->data[2][2]*point->z + matrix->data[2][3];
}

static void applyTranslation(const TransformParams* transform, Point3D* point) {
    point->x += transform->translateX;
    point->y += transform->translateY;
    point->z += transform->translateZ;
}

static void buildTransformMatrix(const TransformParams* transform, Matrix4x4* result) {
    Matrix4x4 scale, rotX, rotY, rotZ, temp;
    makeScale(&scale, transform->scale);
    makeRotationX(&rotX, transform->rotateX);
    makeRotationY(&rotY, transform->rotateY);
    makeRotationZ(&rotZ, transform->rotateZ);
    multiplyMatrices(&scale, &rotX, &temp);
    multiplyMatrices(&temp, &rotY, result);
    multiplyMatrices(result, &rotZ, &temp);
    *result = temp;
}

Status getTransformedPoints(AppContext* context) {
    SceneData* scene = &context->scene;
    int count = scene->rows * scene->columns;
    Status status = NO_ERROR;
    if (scene->transformedPoints == NULL)
        scene->transformedPoints = allocPoints(count);
    if (scene->transformedPoints == NULL)
        status = ERROR_ALLOC_MEMORY;
    else {
        Matrix4x4 matrix;
        buildTransformMatrix(&context->transform, &matrix);
        for (int i = 0; i < count; i++) {
            multiplyMatrixPoint(&matrix, &scene->normalizedPoints[i],
                                &scene->transformedPoints[i]);
            applyTranslation(&context->transform, &scene->transformedPoints[i]);
        }
    }
    return status;
}
