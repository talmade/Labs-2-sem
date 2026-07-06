#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "../constants.h"

typedef enum {
    NO_ERROR,
    BUFFER_OVERLOAD,
    INVALID_CHARACTER
} FlagError;

struct AppContext {
    FlagError flagError;
    char strConvertedNumber[SIZE_ARRAY_SYMBOL];
    char errorPrint[SIZE_ARRAY_SYMBOL];
};

#endif // APPCONTEXT_H
