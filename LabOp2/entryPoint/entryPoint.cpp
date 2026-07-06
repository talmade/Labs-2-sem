#include "entryPoint.h"
#include "../logic/initialization.h"
#include "../logic/loadData.h"
#include "../logic/calculateMetric.h"

void doOperation(Operation operation, AppContext* context, ParamsUser* params) {
    switch (operation) {
    case INITIALIZATION:
        initialize(context);
        break;
    case LOADING_DATA:
        context->flagErrorCode = loadData(context, context->filename);
        break;
    case CALCULATE_METRIC:
        context->flagErrorCode = calculateMetric(context, params);
        break;
    }
}
