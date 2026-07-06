#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "LinkedList.h"
#include "constants.h"

struct Metrics {
    double min;
    double max;
    double median;
};

struct Lines {
    int totalLines;
    int errorLines;
    int successLines;
};

struct AppContext {
    LinkedList* list;
    Metrics metrics;
    Lines lines;
    StatusCode flagErrorCode;
    char* printErrorCode;
    char* filename;
};

#endif // APPCONTEXT_H
