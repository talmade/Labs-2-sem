#ifndef CALCULATORFACADE_H
#define CALCULATORFACADE_H

#include <string>

#include "Operation/operatorFactory.h"
#include "tokenizer.h"
#include "evaluator.h"

class CalculatorFacade {
public:
    CalculatorFacade();
public:
    void input(const std::string& value);
    void deleteLast();
    void clear();
    void calculate();
public:
    const std::string& getDisplay() const noexcept;
private:
    OperatorFactory operatorFactory;
    Tokenizer tokenizer;
    Evaluator evaluator;
    std::string expression;
    bool Calculated = false;
private:
    std::string formatResult(double result) const;
    void validateBrackets() const;
};

#endif // CALCULATORFACADE_H
