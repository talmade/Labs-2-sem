#ifndef CALCULATEMETRIC_H
#define CALCULATEMETRIC_H

#include "appContext.h"
#include "logicConstants.h"

int getColumnOffset(const int*);
StatusCode calculateMetric(AppContext*, const ParamsUser*);

#endif // CALCULATEMETRIC_H
