#include <cmath>
#include <stdexcept>

#include "divideOperator.h"
#include "../constantsLogic.h"

double DivideOperator::execute(double value1, double value2) const {
    if (std::fabs(value2) < ConstantsLogic::Epsilon)
        throw std::runtime_error("Division by zero");
    return value1 / value2;
}

int DivideOperator::priority() const {
    return ConstantsLogic::secondPriority;
}

std::string DivideOperator::toString() const {
    return "/";
}
