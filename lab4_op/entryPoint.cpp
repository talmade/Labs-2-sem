#include "entryPoint.h"
#include "logic/appContext.h"
#include "logic/csvParsing.h"
#include "logic/normalizer.h"
#include "logic/transform.h"
#include "logic/contextManager.h"

#include "logic/errorHandler.h"

void doOperations(Operations operation, AppContext* context) {
    switch(operation) {
    case INITIALIZATION:
        initializeContext(context);
        break;
    case UPLOADING_FILE:
        context->status = loadFile(context);
        if (context->status != NO_ERROR)
            setError(context, context->status);
        break;
    case NORMALIZATION:
        context->status = normalizeModel(context);
        if (context->status != NO_ERROR)
            setError(context, context->status);
        break;
    case TRANSFORMATION:
        context->status = getTransformedPoints(context);
        if (context->status != NO_ERROR)
            setError(context, context->status);
        break;
    case CLEARING:
        freeContext(context);
        break;
    }
}

