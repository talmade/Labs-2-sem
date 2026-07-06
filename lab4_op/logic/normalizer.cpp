#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "normalizer.h"
#include "matrixUtils.h"

static double normalizeValue(AppContext* context, double value);
static Status fillNormalizedPoints(AppContext* context);

Status normalizeModel(AppContext* context) {
    Status status = NO_ERROR;
    SceneData* scene = &context->scene;

    if (scene->normMin >= scene->normMax || scene->step <= 0.)
        status = ERROR_INVALID_RANGE;
    if (status == NO_ERROR && context->rawModel.data == NULL)
        status = ERROR_EMPTY_MODEL;
    if (status == NO_ERROR) {
        freePoints(&scene->normalizedPoints);
        freePoints(&scene->transformedPoints);
        scene->rows = context->rawModel.rows;
        scene->columns = context->rawModel.columns;
        status = fillNormalizedPoints(context);
    }
    return status;
}

static double normalizeValue(AppContext* context, double value) {
    double rawMin = context->rawModel.minValue;
    double rawMax = context->rawModel.maxValue;
    double normMin = context->scene.normMin;
    double normMax = context->scene.normMax;
    double result = normMin;
    if (fabs(rawMax - rawMin) > DBL_EPSILON)
        result = normMin + (value - rawMin) / (rawMax - rawMin) * (normMax - normMin);
    return result;
}

static Status fillNormalizedPoints(AppContext* context) {
    SceneData* scene = &context->scene;
    DataModel* raw = &context->rawModel;
    int count = scene->rows * scene->columns;
    double centerX = (scene->columns - 1) * scene->step / 2.0;
    double centerZ = (scene->rows - 1) * scene->step / 2.0;
    Status status = NO_ERROR;

    scene->normalizedPoints = allocPoints(count);
    if (scene->normalizedPoints == NULL) {
        status = ERROR_ALLOC_MEMORY;
    } else {
        for (int i = 0; i < scene->rows; i++)
            for (int j = 0; j < scene->columns; j++) {
                int idx = i * scene->columns + j;
                scene->normalizedPoints[idx].x = j * scene->step - centerX;
                scene->normalizedPoints[idx].y = normalizeValue(context, raw->data[i][j]);
                scene->normalizedPoints[idx].z = i * scene->step - centerZ;
            }
    }
    return status;
}
