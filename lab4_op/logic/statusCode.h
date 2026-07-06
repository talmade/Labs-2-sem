#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    NO_ERROR,
    ERROR_ALLOC_MEMORY,
    ERROR_READ_FILE,
    ERROR_READ_LINE,
    ERROR_INVALID_RANGE,
    ERROR_EMPTY_MODEL
} Status;

#endif // ERRORS_H
