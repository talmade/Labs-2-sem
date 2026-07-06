#ifndef RIGHTPARENTOKEN_H
#define RIGHTPARENTOKEN_H

#include "operatorToken.h"

class RightParenToken: public OperatorToken {
public:
    explicit RightParenToken(const OperatorFactory& operatorFactory);
    void process(EvalContext& context) const override;
};

#endif // RIGHTPARENTOKEN_H
