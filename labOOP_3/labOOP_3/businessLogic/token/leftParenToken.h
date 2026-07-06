#ifndef LEFTPARENTOKEN_H
#define LEFTPARENTOKEN_H

#include "operatorToken.h"

class LeftParenToken: public OperatorToken {
public:
    explicit LeftParenToken(const OperatorFactory& operatorFactory);
    void process(EvalContext& context) const override;
};

#endif // LEFTPARENTOKEN_H
