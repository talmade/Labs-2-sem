#include <cctype>
#include <stdexcept>

#include "tokenizer.h"
#include "token/numberToken.h"
#include "token/binaryOperatorToken.h"
#include "token/leftParenToken.h"
#include "token/rightParenToken.h"


Tokenizer::Tokenizer(const OperatorFactory& operatorFactory)
    : operatorFactory(operatorFactory) {}

std::vector<std::unique_ptr<Token>> Tokenizer::tokenize(const std::string& expression) const {
    std::vector<std::unique_ptr<Token>> tokens;

    size_t pos = 0;
    while (pos < expression.size()) {
        char symbol = expression[pos];

        if (std::isdigit(symbol) || symbol == '.') {
            std::string number;
            int dotCount = 0;
            while (pos < expression.size() &&
                   (std::isdigit(expression[pos]) || expression[pos] == '.')) {
                if (expression[pos] == '.' && ++dotCount > 1)
                    throw std::runtime_error("Invalid number: multiple dots");
                number += expression[pos++];
            }
            tokens.push_back(std::make_unique<NumberToken>(number));

        } else if (symbol == '(') {
            tokens.push_back(std::make_unique<LeftParenToken>(operatorFactory));
            ++pos;

        } else if (symbol == ')') {
            tokens.push_back(std::make_unique<RightParenToken>(operatorFactory));
            ++pos;

        } else if (operatorFactory.isKnown(std::string(1, symbol))) {
            bool isUnary = (symbol == '-') &&
                           (tokens.empty() || tokens.back()->getValue() == "(");
            if (isUnary)
                tokens.push_back(std::make_unique<NumberToken>("0"));

            tokens.push_back(std::make_unique<BinaryOperatorToken>(
                std::string(1, symbol), operatorFactory));
            ++pos;

        } else
            throw std::runtime_error(std::string("Unexpected character: ") + symbol);
    }

    return tokens;
}
