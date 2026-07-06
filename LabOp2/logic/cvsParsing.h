#ifndef CVSPARSING_H
#define CVSPARSING_H

#include "AppParams.h"

typedef enum {
    NO_LAST,
    LAST
} Place;

char* doNextField(char**, int);
int doParseFieldInt(char**, int*, int);
int doParseFieldDouble(char**, double*, int);
int doParseFieldString(char**, char**, int);
int doParseLine(const char*, TableParams*);

#endif // CVSPARSING_H
