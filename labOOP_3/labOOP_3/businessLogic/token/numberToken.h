#ifndef NUMBERTOKEN_H
#define NUMBERTOKEN_H

#include "token.h"

class NumberToken: public Token {
public:
    explicit NumberToken(std::string value);
    void process(EvalContext& context) const override;
    std::string getValue() const override;
private:
    std::string value;
};

#endif // NUMBERTOKEN_H
