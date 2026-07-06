#ifndef DIVIDEOPERATOR_H
#define DIVIDEOPERATOR_H

#include "operator.h"

class DivideOperator: public Operator {
public:
    double execute(double value1, double value2) const override;
    int priority() const override;
    std::string toString() const override;
};

#endif // DIVIDEOPERATOR_H
