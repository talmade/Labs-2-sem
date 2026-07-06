#ifndef SUBTRACTOPERATOR_H
#define SUBTRACTOPERATOR_H

#include "operator.h"

class SubtractOperator : public Operator {
public:
    double execute(double value1, double value2) const override;
    int priority() const override;
    std::string toString() const override;
};

#endif // SUBTRACTOPERATOR_H
