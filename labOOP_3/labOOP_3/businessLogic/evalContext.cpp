#include <stdexcept>

#include "evalContext.h"
#include "constantsLogic.h"

EvalContext::EvalContext(const OperatorFactory& operatorFactory)
    : operatorFactory(operatorFactory) {}

void EvalContext::applyTop() {
    if (values.size() < ConstantsLogic::minOperandCount || operators.empty())
        throw std::runtime_error("Not enough operands");

    double right = values.back(); values.pop_back();
    double left  = values.back(); values.pop_back();

    double result = operatorFactory.create(operators.back())->execute(left, right);
    operators.pop_back();
    values.push_back(result);
}
