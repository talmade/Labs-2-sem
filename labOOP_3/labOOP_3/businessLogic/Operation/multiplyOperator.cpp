#include "multiplyOperator.h"
#include "../constantsLogic.h"

double MultiplyOperator::execute(double value1, double value2) const {
    return value1 * value2;
}

int MultiplyOperator::priority() const {
    return ConstantsLogic::secondPriority;
}

std::string MultiplyOperator::toString() const {
    return "*";
}
