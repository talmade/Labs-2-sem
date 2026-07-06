#include <stdlib.h>

#include "stringUtils.h"

char* allocBuffer() {
    return (char*) malloc(BUFFER_SIZE);
}

void freeBuffer(char* buffer) {
    free(buffer);
}
