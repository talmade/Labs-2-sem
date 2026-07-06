#include <stdlib.h>

#include "stringMemory.h"

char* allocForString(SIZE size) {return (char*) malloc(size);}

void freeString(char* string) {free(string);}


