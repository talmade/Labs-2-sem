#include "subtractOperator.h"
#include "../constantsLogic.h"

double SubtractOperator::execute(double value1, double value2) const {
    return value1 - value2;
}

int SubtractOperator::priority() const {
    return ConstantsLogic::firstPriority;
}

std::string SubtractOperator::toString() const {
    return "-";
}
