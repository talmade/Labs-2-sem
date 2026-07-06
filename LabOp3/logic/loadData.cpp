#include <stdio.h>

#include "loadData.h"
#include "logicConstants.h"
#include "cvsParsing.h"
#include "LinkedList.h"
#include "appContext.h"
#include "stringMemory.h"

StatusCode loadData(AppContext* context, const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL)
        return ERROR_READ_FILE;

    LinkedList* list = listCreate();
    char* buffer = allocForString(SIZE_BUFFER);
    while(fgets(buffer, SIZE_BUFFER, file) != NULL) {
        context->lines.totalLines++;

        TableParams params;
        params.republic = NULL;

        if (doParseLine(buffer, &params) == NO_ERROR) {
            listPushBack(list, &params);
            freeString(params.republic);
            context->lines.successLines++;
        } else {
            freeString(params.republic);
            context->lines.errorLines++;
        }
    }

    freeString(buffer);
    context->list = list;
    fclose(file);

    return SUCCESSFULLY;
}
