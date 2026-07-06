#include <stdexcept>

#include "rightParenToken.h"

RightParenToken::RightParenToken(const OperatorFactory& operatorFactory)
    : OperatorToken(")", operatorFactory) {}

void RightParenToken::process(EvalContext& context) const {
    while (!context.operators.empty() && context.operators.back() != "(")
        context.applyTop();

    if (context.operators.empty())
        throw std::runtime_error("Mismatched brackets");

    context.operators.pop_back();
}
