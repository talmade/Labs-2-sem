#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
    virtual void execute(std::string& expression) = 0;
    virtual ~Command() = default;
};

#endif // COMMAND_H
