#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "../evalContext.h"

class Token {
public:
    virtual void process(EvalContext& context) const = 0;
    virtual std::string getValue() const = 0;
    virtual ~Token() = default;
};

#endif // TOKEN_H
