#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "logic.h"

void initialize(AppContext* context) {
    strcpy(context->strConvertedNumber, DEFAULT_FIELD);
    context->flagError = NO_ERROR;
}

void validateNumber(AppContext* context, AppParams* params) {
    switch(params->startNumSystem) {
    case DECIMAL:
        validateDecimal(context, params);
        break;
    case OCTA:
        validateNumberOfAdditionCode(context, params, UP_BORDER_OCTA);
        break;
    case BINARY:
        validateNumberOfAdditionCode(context, params, UP_BORDER_BINARY);
    }
}

void validateDecimal(AppContext* context, AppParams* params) {
    char* userValStr = params->strUserValue;

    if (!(userValStr[FIRST_SYMBOL] == '-' || (isdigit(userValStr[FIRST_SYMBOL]))) && !context->flagError)
        context->flagError = INVALID_CHARACTER;

    for (unsigned i = SECOND_SYMBOL; i < strlen(userValStr) && !context->flagError; ++i)
        if (!isdigit(userValStr[i]))
            context->flagError = INVALID_CHARACTER;

    if (!context->flagError) {
        long long result = strtoll(userValStr, NULL, params->startNumSystem);
        if (!(INT_MIN <= result && result <= INT_MAX))
            context->flagError = BUFFER_OVERLOAD;
    }

    doErrorTransfer(context, context->flagError);
}

void validateNumberOfAdditionCode(AppContext* context, AppParams* params, NumSystemBorder upBorder) {
    char* userValStr = params->strUserValue;

    for (unsigned i = FIRST_SYMBOL; i < strlen(userValStr) && !context->flagError; ++i)
        if (userValStr[i] < LOW_BORDER || userValStr[i] > upBorder)
            context->flagError = INVALID_CHARACTER;

    if (!context->flagError) {
        long long result = strtoll(userValStr, NULL, params->startNumSystem);
        if ((result < 0 || result > (long long)UINT32_MAX))
            context->flagError = BUFFER_OVERLOAD;
    }

    doErrorTransfer(context, context->flagError);
}

void doErrorTransfer(AppContext* context, FlagError flag) {
    switch(flag) {
    case INVALID_CHARACTER:
        strcpy(context->errorPrint, "The number contains an invalid character");
        break;
    case BUFFER_OVERLOAD:
        strcpy(context->errorPrint, "The number does not fit into the 4 byte range");
        break;
    case NO_ERROR:
        break;
    }
}

void convertNumber(AppContext* context, AppParams* params) {
    switch(params->endNumSystem) {
    case DECIMAL:
        convertToDecimal(context, params);
        break;
    case OCTA:
        convertToOcta(context, params);
        break;
    case BINARY:
        convertToBinary(context, params);
        break;
    }
}

void convertToDecimal(AppContext* context, AppParams* params) {
    int32_t userValueNum = (int32_t) strtoll(params->strUserValue, NULL, params->startNumSystem);

    snprintf(context->strConvertedNumber, SIZE_ARRAY_SYMBOL, "%d", userValueNum);
}

void convertToBinary(AppContext* context, AppParams* params) {
    int32_t userValueNum = (int32_t) strtoll(params->strUserValue, NULL, params->startNumSystem);

    for (int i = LAST_INDEX_BINARY; i >= FIRST_SYMBOL; --i)
        context->strConvertedNumber[LAST_INDEX_BINARY - i] = ((userValueNum >> i) & MASK_BINARY) + '0';
    context->strConvertedNumber[LAST_INDEX_BINARY + 1] = '\0';
}

void convertToOcta(AppContext* context, AppParams* params) {
    int32_t userValueNum = (int32_t) strtoll(params->strUserValue, NULL, params->startNumSystem);

    context->strConvertedNumber[FIRST_SYMBOL] = ((userValueNum >> FIRST_SHIFT_OCTA) & MASK_FIRST_SYMBOL_OCTA) + '0';
    for (int i = LAST_INDEX_OCTA - 1; i >= FIRST_SYMBOL; --i)
        context->strConvertedNumber[LAST_INDEX_OCTA - i] = ((userValueNum >> (i * SHIFT_OCTA)) & MASK_OCTA) + '0';
    context->strConvertedNumber[LAST_INDEX_OCTA + 1] = '\0';
}

void swapNumberSystem(AppContext* context, AppParams* params) {
    int tempInt = params->startNumSystem;
    params->startNumSystem = params->endNumSystem;
    params->endNumSystem = tempInt;

    char tempStr[SIZE_ARRAY_SYMBOL];
    strncpy(tempStr, context->strConvertedNumber, SIZE_ARRAY_SYMBOL - 1);
    strncpy(context->strConvertedNumber, params->strUserValue, SIZE_ARRAY_SYMBOL - 1);
    strncpy(params->strUserValue, tempStr, SIZE_ARRAY_SYMBOL - 1);
}



