#include <stdlib.h>
#include <string.h>

#include "contextManager.h"
#include "matrixUtils.h"
#include "stringUtils.h"

static void initRawModel(DataModel* model);
static void initScene(SceneData* scene);
static void initTransform(TransformParams* transform);

void initializeContext(AppContext* context) {
    initRawModel(&context->rawModel);
    initScene(&context->scene);
    initTransform(&context->transform);
    context->errorMessage = NULL;
    context->filename = allocBuffer();
    context->status = NO_ERROR;
}

static void initRawModel(DataModel* model) {
    model->data = NULL;
    model->rows = 0;
    model->columns = 0;
    model->minValue = 0.;
    model->maxValue = 0.;
}

static void initScene(SceneData* scene) {
    scene->normalizedPoints = NULL;
    scene->transformedPoints = NULL;
    scene->rows = 0;
    scene->columns = 0;
    scene->normMin = 0.;
    scene->normMax = 1.;
    scene->step = 1.;
}

static void initTransform(TransformParams* transform) {
    transform->rotateX = 0.;
    transform->rotateY = 0.;
    transform->rotateZ = 0.;
    transform->translateX = 0.;
    transform->translateY = 0.;
    transform->translateZ = 0.;
    transform->scale = 1.;
}

void freeContext(AppContext* context) {
    freeBuffer(context->filename);
    freeBuffer(context->errorMessage);
    freeMatrix(context->rawModel.data, context->rawModel.rows);
    freePoints(&context->scene.normalizedPoints);
    freePoints(&context->scene.transformedPoints);
}
