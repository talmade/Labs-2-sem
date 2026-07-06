#ifndef ADDOPERATOR_H
#define ADDOPERATOR_H

#include "operator.h"

class AddOperator: public Operator {
public:
    double execute(double value1, double value2) const override;
    int priority() const override;
    std::string toString() const override;
};

#endif // ADDOPERATOR_H
