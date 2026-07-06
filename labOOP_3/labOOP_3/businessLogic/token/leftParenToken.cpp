#include "leftParenToken.h"

LeftParenToken::LeftParenToken(const OperatorFactory& operatorFactory)
    : OperatorToken("(", operatorFactory) {}

void LeftParenToken::process(EvalContext& context) const {
    context.operators.push_back("(");
}
