#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H

#include "сommand.h"

class ClearCommand: public Command {
public:
    void execute(std::string& expression) override;
};

#endif // CLEARCOMMAND_H
