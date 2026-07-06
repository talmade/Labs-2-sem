#ifndef EVALCONTEXT_H
#define EVALCONTEXT_H

#include <vector>
#include <string>

#include "Operation/operatorFactory.h"

class EvalContext {
public:
    explicit EvalContext(const OperatorFactory& operatorFactory);
    void applyTop();
public:
    std::vector<double> values;
    std::vector<std::string> operators;
private:
    const OperatorFactory& operatorFactory;
};

#endif // EVALCONTEXT_H
