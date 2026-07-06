#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>

class Operator {
public:
    virtual double execute(double value1, double value2) const = 0;
    virtual int priority() const = 0;
    virtual std::string toString() const = 0;
    virtual ~Operator() = default;
};

#endif // OPERATOR_H
