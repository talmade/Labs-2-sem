#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum {
    NO_ERROR,
    ERROR_READ_LINE,
    ERROR_READ_FIELD,
    EMPTY_LINE,
} Error;

typedef enum {
    OFFSET_UNDEFINED = -1,
    SUCCESSFULLY,
    ERROR_READ_FILE,
    EMPTY_LIST,
    ARRAY_NOT_CREATE,
    EMPTY_ARRAY,
    FILE_NOT_SELECT
} StatusCode;

typedef enum {
    SIZE_FIELD = 64,
    SIZE_BUFFER = 256
} SIZE;

typedef enum {
    YEAR = 1,
    REPUBLIC,
    NPG,
    BIRTH_RATE,
    DEATH_RATE,
    GDW,
    URBANIZATION
} NameColumnn;

#endif // CONSTANTS_H
