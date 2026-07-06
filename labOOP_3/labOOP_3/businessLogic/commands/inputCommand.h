#ifndef INPUTCOMMAND_H
#define INPUTCOMMAND_H

#include "сommand.h"

class InputCommand: public Command {
public:
    explicit InputCommand(std::string input);
    void execute(std::string& expression) override;
private:
    std::string input;
};

#endif // INPUTCOMMAND_H
