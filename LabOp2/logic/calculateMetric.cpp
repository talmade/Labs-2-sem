#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "calculateMetric.h"
#include "Iterator.h"
#include "sort.h"

#define TWO 2

StatusCode calculateMetric(AppContext* context, const ParamsUser* paramsUser) {
    if (context->list == NULL || getSizeList(context->list) == 0)
        context->flagErrorCode = EMPTY_LIST;

    int offset = OFFSET_UNDEFINED;
    if (context->flagErrorCode == SUCCESSFULLY) {
        offset = getColumnOffset(&paramsUser->column);
        if (offset == OFFSET_UNDEFINED)
            context->flagErrorCode = OFFSET_UNDEFINED;
    }

    double* valuesColumn = NULL;
    if (context->flagErrorCode == SUCCESSFULLY) {
        valuesColumn = allocForArrayDouble(getSizeList(context->list));
        if (valuesColumn == NULL)
            context->flagErrorCode = ARRAY_NOT_CREATE;
    }

    size_t sizeValuesColumn = 0;
    if (context->flagErrorCode == SUCCESSFULLY) {
        Iterator iter = iteratorCreate(context->list);

        while(iteratorHasNext(&iter)) {
            TableParams* data = iteratorNext(&iter);

            if (strcmp(paramsUser->republic, data->republic) == 0) {
                valuesColumn[sizeValuesColumn] = *(double*)((char*) data + offset);
                sizeValuesColumn++;
            }
        }
    }

    if (context->flagErrorCode == SUCCESSFULLY && sizeValuesColumn == 0)
        context->flagErrorCode = EMPTY_ARRAY;

    if (context->flagErrorCode == SUCCESSFULLY) {
        sortDoubles(valuesColumn, sizeValuesColumn);

        context->metrics.min = valuesColumn[0];
        context->metrics.max = valuesColumn[sizeValuesColumn - 1];

        if (sizeValuesColumn % TWO == 0)
            context->metrics.median = (valuesColumn[sizeValuesColumn / TWO - 1]  + valuesColumn[sizeValuesColumn / TWO]) / (double) TWO;
        else
            context->metrics.median = valuesColumn[(sizeValuesColumn - 1) / TWO];
    }

    freeArrayDouble(valuesColumn);
    return context->flagErrorCode;
}

int getColumnOffset(const int* column) {
    int offset = OFFSET_UNDEFINED;

    if (*column >= 3 && *column <= 7) {
        switch (*column) {
        case NPG:
            offset = offsetof(TableParams, npg);
            break;
        case BIRTH_RATE:
            offset = offsetof(TableParams, birthRate);
            break;
        case DEATH_RATE:
            offset = offsetof(TableParams, deathRate);
            break;
        case GDW:
            offset = offsetof(TableParams, gdw);
            break;
        case URBANIZATION:
            offset = offsetof(TableParams, urbanization);
            break;
        }
    }
    return offset;
}

double* allocForArrayDouble(const size_t size) {return (double*) malloc(size * sizeof(double));}

void freeArrayDouble(double* array) {free(array);}






