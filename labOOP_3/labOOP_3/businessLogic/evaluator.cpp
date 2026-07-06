#include <stdexcept>

#include "evaluator.h"
#include "evalContext.h"

double Evaluator::evaluate(const std::vector<std::unique_ptr<Token>>& tokens,
                           const OperatorFactory& operatorFactory) const {
    EvalContext context(operatorFactory);

    for (const auto& token : tokens)
        token->process(context);

    while (!context.operators.empty()) {
        if (context.operators.back() == "(")
            throw std::runtime_error("Mismatched brackets");
        context.applyTop();
    }

    if (context.values.size() != 1)
        throw std::runtime_error("Invalid expression");

    return context.values.back();
}
