#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "../logic/appContext.h"

typedef enum {
    INITIALIZATION,
    LOADING_DATA,
    CALCULATE_METRIC
} Operation;

void doOperation(Operation, AppContext*, ParamsUser*);
#endif // ENTRYPOINT_H
