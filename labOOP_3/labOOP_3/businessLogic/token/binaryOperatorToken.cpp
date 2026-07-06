#include "binaryOperatorToken.h"

BinaryOperatorToken::BinaryOperatorToken(std::string symbol,
                                         const OperatorFactory& operatorFactory)
    : OperatorToken(std::move(symbol), operatorFactory) {}

void BinaryOperatorToken::process(EvalContext& context) const {
    while (!context.operators.empty() &&
           context.operators.back() != "(" &&
           operatorFactory.getPriority(context.operators.back()) >= operatorFactory.getPriority(getValue()))
        context.applyTop();

    context.operators.push_back(getValue());
}
