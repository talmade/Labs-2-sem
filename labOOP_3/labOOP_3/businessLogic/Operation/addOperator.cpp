#include "addOperator.h"
#include "../constantsLogic.h"

double AddOperator::execute(double value1, double value2) const {
    return value1 + value2;
}

int AddOperator::priority() const {
    return ConstantsLogic::firstPriority;
}

std::string AddOperator::toString() const {
    return "+";
}
