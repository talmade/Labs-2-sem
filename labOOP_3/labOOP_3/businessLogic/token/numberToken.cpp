#include "numberToken.h"

NumberToken::NumberToken(std::string value): value(std::move(value)) {}

std::string NumberToken::getValue() const { return value; }

void NumberToken::process(EvalContext& context) const {
    context.values.push_back(std::stod(value));
}
