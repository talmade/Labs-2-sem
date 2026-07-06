#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "logic/appContext.h"

typedef enum {
    INITIALIZATION,
    UPLOADING_FILE,
    NORMALIZATION,
    TRANSFORMATION,
    CLEARING
} Operations;

void doOperations(Operations operation, AppContext* context);

#endif // ENTRYPOINT_H
