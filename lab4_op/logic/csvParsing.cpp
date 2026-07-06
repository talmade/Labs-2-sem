#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "csvParsing.h"
#include "appContext.h"
#include "matrixUtils.h"
#include "stringUtils.h"

#define BUFFER_SIZE 4096

static char* doNextField(char** pos) {
    char* result = NULL;
    if (*pos != NULL) {
        char* start = *pos;
        char* comma = strchr(start, ',');
        if (comma != NULL) {
            *comma = '\0';
            *pos = comma + 1;
        } else
            *pos = NULL;
        if (strlen(start) > 0)
            result = start;
    }
    return result;
}

static Status doParseFieldDouble(char** pos, double* out) {
    char* field = doNextField(pos);
    Status status = NO_ERROR;
    if (field == NULL)
        status = ERROR_READ_LINE;
    else {
        char *end;
        *out = strtod(field, &end);
        status = (*end != '\0') ? ERROR_READ_LINE : NO_ERROR;
    }
    return status;
}

static void trimLineEnding(char* line) {
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        line[--len] = '\0';
}

static int doParseRowCount(char* line, double* minValue, double* maxValue) {
    char* pos = line;
    int count = 0;
    double value;
    while (doParseFieldDouble(&pos, &value) == NO_ERROR) {
        if (value < *minValue)
            *minValue = value;
        if (value > *maxValue)
            *maxValue = value;
        count++;
    }
    return count;
}

static void doParseRowIntoMatrix(char* line, double* row, int columns) {
    char* pos = line;
    int col = 0;
    double value;
    while (col < columns && doParseFieldDouble(&pos, &value) == NO_ERROR) {
        row[col] = value;
        col++;
    }
    while (col < columns) {
        row[col] = 0.;
        col++;
    }
}

static Status findModelParams(FILE* file, DataModel* model) {
    char* buffer = allocBuffer();
    Status status = ERROR_ALLOC_MEMORY;
    if (buffer != NULL) {
        model->rows = 0;
        model->columns = 0;
        model->minValue = DBL_MAX;
        model->maxValue = -DBL_MAX;

        while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
            trimLineEnding(buffer);
            if (strlen(buffer) > 0) {
                int count = doParseRowCount(buffer, &model->minValue, &model->maxValue);
                if (count > model->columns)
                    model->columns = count;
                model->rows++;
            }
        }

        status = (model->rows == 0 || model->columns == 0) ? ERROR_EMPTY_MODEL : NO_ERROR;
        free(buffer);
    }
    return status;
}

static Status fillModelData(FILE* file, DataModel* model) {
    char* buffer = allocBuffer();
    Status status = ERROR_ALLOC_MEMORY;
    if (buffer != NULL) {
        int row = 0;
        while (fgets(buffer, BUFFER_SIZE, file) != NULL && row < model->rows) {
            trimLineEnding(buffer);
            if (strlen(buffer) > 0) {
                doParseRowIntoMatrix(buffer, model->data[row], model->columns);
                row++;
            }
        }
        status = NO_ERROR;
        free(buffer);
    }
    return status;
}


Status loadFile(AppContext* context) {
    FILE* file = fopen(context->filename, "r");
    Status status = ERROR_READ_FILE;
    if (file != NULL) {
        status = findModelParams(file, &context->rawModel);
        if (status == NO_ERROR) {
            rewind(file);
            context->rawModel.data = allocMatrix(context->rawModel.rows, context->rawModel.columns);
            if (context->rawModel.data == NULL)
                status = ERROR_ALLOC_MEMORY;
        }
        if (status == NO_ERROR)
            status = fillModelData(file, &context->rawModel);
        fclose(file);
    }
    return status;
}
