#include "initialization.h"
#include "constants.h"
#include "stringMemory.h"

void initialize(AppContext* context) {
    context->metrics.max = 0;
    context->metrics.min = 0;
    context->metrics.median = 0;

    context->lines.errorLines = 0;
    context->lines.successLines = 0;
    context->lines.totalLines = 0;

    context->list = NULL;

    context->flagErrorCode = SUCCESSFULLY;

    context->printErrorCode = allocForString(SIZE_BUFFER);
    context->filename = allocForString(SIZE_BUFFER);
}


