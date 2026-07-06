#ifndef LOGIC_H
#define LOGIC_H

#include "appContext.h"
#include "appParams.h"

enum NumSystem {
    BINARY = 2,
    OCTA = 8,
    DECIMAL = 10
};

enum NumSystemBorder {
    LOW_BORDER = '0',
    UP_BORDER_BINARY = '1',
    UP_BORDER_OCTA = '7'
};

typedef enum {
    FIRST_SYMBOL,
    SECOND_SYMBOL
} SymbolIndex;

typedef enum {
    LAST_INDEX_BINARY = 31,
    LAST_INDEX_OCTA = 10,
} INDEX;

typedef enum {
    MASK_OCTA = 7,
    MASK_FIRST_SYMBOL_OCTA = 3,
    MASK_BINARY = 1
} MASK;

typedef enum {
    SHIFT_OCTA = 3,
    FIRST_SHIFT_OCTA = 30
} SHIFT;

void initialize(AppContext*);
void validateNumber(AppContext*, AppParams*);
void validateDecimal(AppContext*, AppParams*);
void validateNumberOfAdditionCode(AppContext*, AppParams*, NumSystemBorder);
void doErrorTransfer(AppContext*, FlagError);
void convertNumber(AppContext*, AppParams*);
void convertToDecimal(AppContext*, AppParams*);
void convertToOcta(AppContext*, AppParams*);
void convertToBinary(AppContext*, AppParams*);
void swapNumberSystem(AppContext*, AppParams*);

#endif // LOGIC_H
