#include <stdlib.h>
#include <string.h>

#include "cvsParsing.h"
#include "constants.h"
#include "stringMemory.h"

#define DECIMAL 10

char* doNextField(char** pos, int isLast) {
    char* result = NULL;

    if (*pos != NULL) {
        char* start = *pos;

        if (isLast)
            *pos = NULL;
        else {
            char* comma = strchr(start, ',');
            if (comma != NULL) {
                *comma = '\0';
                *pos = comma + 1;
            } else
                *pos = NULL;
        }

        if (strlen(start) > 0)
            result = start;
    }

    return result;
}

int doParseFieldInt(char** pos, int* out, int isLast) {
    char* field = doNextField(pos, isLast);
    int error = NO_ERROR;

    if (field == NULL)
        error = ERROR_READ_FIELD;
    else {
        char* end;
        *out = (int) strtol(field, &end, DECIMAL);
        error = (*end != '\0') ? ERROR_READ_FIELD : NO_ERROR;
    }

    return error;
}

int doParseFieldDouble(char** pos, double* out, int isLast) {
    char* field = doNextField(pos, isLast);
    int error = NO_ERROR;

    if (field == NULL)
        error = ERROR_READ_FIELD;
    else {
        char* end;
        *out = strtod(field, &end);
        error = (*end != '\0') ? ERROR_READ_FIELD : NO_ERROR;
    }

    return error;
}

int doParseFieldString(char** pos, char** out, int isLast) {
    char* field = doNextField(pos, isLast);
    int error = NO_ERROR;

    if (field == NULL)
        error = ERROR_READ_FIELD;
    else {
        *out = allocForString(SIZE_FIELD);
        strncpy(*out, field, SIZE_FIELD - 1);
    }

    return error;
}

int doParseLine(const char* line, TableParams* params) {
    char* buffer = allocForString(SIZE_BUFFER);
    strncpy(buffer, line, SIZE_BUFFER - 1);

    size_t lenBuf = strlen(buffer);
    while (lenBuf > 0 && (buffer[lenBuf - 1] == '\n' || buffer[lenBuf - 1] == '\r')) {
        buffer[lenBuf - 1] = '\0';
        lenBuf--;
    }

    int parsing = NO_ERROR;
    if (lenBuf == 0)
        parsing = EMPTY_LINE;
    else {
        char *pos = buffer;

        int unsuccesField = 0;
        unsuccesField += doParseFieldInt(&pos, &params->year, NO_LAST);
        unsuccesField += doParseFieldString(&pos, &params->republic, NO_LAST);
        unsuccesField += doParseFieldDouble(&pos, &params->npg, NO_LAST);
        unsuccesField += doParseFieldDouble(&pos, &params->birthRate, NO_LAST);
        unsuccesField += doParseFieldDouble(&pos, &params->deathRate, NO_LAST);
        unsuccesField += doParseFieldDouble(&pos, &params->gdw, NO_LAST);
        unsuccesField += doParseFieldDouble(&pos, &params->urbanization, LAST);

        parsing = unsuccesField == 0 ? NO_ERROR : ERROR_READ_LINE;
    }

    freeString(buffer);
    return parsing;
}
