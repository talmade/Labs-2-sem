#include <string.h>
#include "errorHandler.h"
#include "stringUtils.h"

void setError(AppContext* context, Status status) {
    freeBuffer(context->errorMessage);
    context->errorMessage = allocBuffer();
    if (context->errorMessage != NULL) {
        switch (status) {
        case ERROR_READ_FILE:
            strncpy(context->errorMessage, "Failed to open file", BUFFER_SIZE - 1);
            break;
        case ERROR_ALLOC_MEMORY:
            strncpy(context->errorMessage, "Memory allocation failed", BUFFER_SIZE - 1);
            break;
        case ERROR_READ_LINE:
            strncpy(context->errorMessage, "Failed to read data from file", BUFFER_SIZE - 1);
            break;
        case ERROR_INVALID_RANGE:
            strncpy(context->errorMessage, "Invalid range: normMin must be less than normMax and step > 0", BUFFER_SIZE - 1);
            break;
        case ERROR_EMPTY_MODEL:
            strncpy(context->errorMessage, "File is empty or contains no valid data", BUFFER_SIZE - 1);
            break;
        case NO_ERROR:
            break;
        }
    }
}
