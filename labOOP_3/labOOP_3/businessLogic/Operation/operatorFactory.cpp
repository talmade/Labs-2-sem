#include <stdexcept>

#include "operatorFactory.h"
#include "addOperator.h"
#include "subtractOperator.h"
#include "multiplyOperator.h"
#include "divideOperator.h"

OperatorFactory::OperatorFactory() {
    makers["+"] = [] { return std::make_unique<AddOperator>(); };
    makers["-"] = [] { return std::make_unique<SubtractOperator>(); };
    makers["*"] = [] { return std::make_unique<MultiplyOperator>(); };
    makers["/"] = [] { return std::make_unique<DivideOperator>(); };
}

bool OperatorFactory::isKnown(const std::string& symbol) const {
    return makers.count(symbol) > 0;
}

std::unique_ptr<Operator> OperatorFactory::create(const std::string& symbol) const {
    auto it = makers.find(symbol);
    if (it == makers.end())
        throw std::runtime_error("Unknown operator: " + symbol);
    return it->second();
}

int OperatorFactory::getPriority(const std::string& symbol) const {
    return create(symbol)->priority();
}
