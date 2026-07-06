#ifndef MENUCOMMANDS_H
#define MENUCOMMANDS_H

#include <string>

class MenuCommands {
public:
    virtual void execute() = 0;
    virtual std::string getLabel() const = 0;

    virtual ~MenuCommands() = default;
};

#endif // MENUCOMMANDS_H
