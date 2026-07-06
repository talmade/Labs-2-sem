#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "logic/appContext.h"
#include "logic/appParams.h"

typedef enum {
    CONVERTION,
    VALIDATION,
    INITIALIZATION,
    SWAP
} Operation;

void doOperation(Operation, AppContext*, AppParams*);

#endif // ENTRYPOINT_H
