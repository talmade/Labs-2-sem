#include <stdexcept>

#include "calculatorFacade.h"
#include "commands/inputCommand.h"
#include "commands/deleteCommand.h"
#include "commands/clearCommand.h"

CalculatorFacade::CalculatorFacade() : tokenizer(operatorFactory) {}

void CalculatorFacade::input(const std::string& value) {
    Calculated = false;
    InputCommand(value).execute(expression);
}

void CalculatorFacade::deleteLast() {
    if (Calculated) {
        ClearCommand().execute(expression);
        Calculated = false;
    } else
        DeleteCommand().execute(expression);
}

void CalculatorFacade::clear() {
    Calculated = false;
    ClearCommand().execute(expression);
}

void CalculatorFacade::calculate() {
    if (!expression.empty()) {

        validateBrackets();

        double result = evaluator.evaluate(tokenizer.tokenize(expression), operatorFactory);
        expression = formatResult(result);
        Calculated = true;
    }
}

const std::string& CalculatorFacade::getDisplay() const noexcept {
    return expression;
}

void CalculatorFacade::validateBrackets() const {
    int count = 0;
    for (char symbol : expression) {
        if (symbol == '(')
            ++count;
        if (symbol == ')')
            --count;
        if (count < 0)
            throw std::runtime_error("Unexpected closing bracket");
    }
    if (count != 0)
        throw std::runtime_error("Unclosed bracket");
}

std::string CalculatorFacade::formatResult(double result) const {
    std::string s = std::to_string(result);
    auto dotPos = s.find('.');
    if (dotPos != std::string::npos) {
        auto lastNonZero = s.find_last_not_of('0');
        s.erase(lastNonZero == dotPos ? dotPos : lastNonZero + 1);
    }
    return s;
}
