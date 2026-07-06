#include "operatorToken.h"

OperatorToken::OperatorToken(std::string symbol, const OperatorFactory& operatorFactory)
    : operatorFactory(operatorFactory), symbol(std::move(symbol)) {}

std::string OperatorToken::getValue() const { return symbol; }
