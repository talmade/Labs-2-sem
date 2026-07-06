#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <memory>
#include <string>

#include "token/token.h"
#include "Operation/operatorFactory.h"

class Tokenizer {
public:
    explicit Tokenizer(const OperatorFactory& operatorFactory);
    std::vector<std::unique_ptr<Token>> tokenize(const std::string& expression) const;
private:
    const OperatorFactory& operatorFactory;
};

#endif // TOKENIZER_H
