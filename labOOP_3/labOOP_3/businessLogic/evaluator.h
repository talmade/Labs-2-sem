#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <memory>

#include "token/token.h"
#include "Operation/operatorFactory.h"

class Evaluator {
public:
    double evaluate(const std::vector<std::unique_ptr<Token>>& tokens,
                    const OperatorFactory& operatorFactory) const;
};

#endif // EVALUATOR_H
