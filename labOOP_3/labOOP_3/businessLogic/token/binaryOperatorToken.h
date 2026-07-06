#ifndef BINARYOPERATORTOKEN_H
#define BINARYOPERATORTOKEN_H

#include "operatorToken.h"

class BinaryOperatorToken: public OperatorToken {
public:
    BinaryOperatorToken(std::string symbol, const OperatorFactory& operatorFactory);
    void process(EvalContext& context) const override;
};

#endif // BINARYOPERATORTOKEN_H
