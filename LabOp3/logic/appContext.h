#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "LinkedList.h"
#include "logicConstants.h"

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
    double* valuesMetric;
};

void initialize(AppContext*);

#endif // APPCONTEXT_H
