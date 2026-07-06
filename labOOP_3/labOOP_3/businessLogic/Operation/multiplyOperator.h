#ifndef MULTIPLYOPERATOR_H
#define MULTIPLYOPERATOR_H

#include "operator.h"

class MultiplyOperator: public Operator {
public:
    double execute(double value1, double value2) const override;
    int priority() const override;
    std::string toString() const override;
};

#endif // MULTIPLYOPERATOR_H
