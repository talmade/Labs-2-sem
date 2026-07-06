#ifndef OPERATORFACTORY_H
#define OPERATORFACTORY_H

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "operator.h"

class OperatorFactory {
public:
    OperatorFactory();
    std::unique_ptr<Operator> create(const std::string& symbol) const;
    int getPriority(const std::string& symbol) const;
    bool isKnown(const std::string& symbol) const;
private:
    std::map<std::string, std::function<std::unique_ptr<Operator>()>> makers;
};

#endif // OPERATORFACTORY_H
