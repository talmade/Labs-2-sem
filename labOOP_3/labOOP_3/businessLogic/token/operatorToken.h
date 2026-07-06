#ifndef OPERATORTOKEN_H
#define OPERATORTOKEN_H

#include "token.h"
#include "../Operation/operatorFactory.h"

class OperatorToken: public Token {
public:
    OperatorToken(std::string symbol, const OperatorFactory& operatorFactory);
    std::string getValue() const override;
protected:
    const OperatorFactory& operatorFactory;
private:
    std::string symbol;
};

#endif // OPERATORTOKEN_H
