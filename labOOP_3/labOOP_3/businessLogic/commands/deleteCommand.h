#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "сommand.h"

class DeleteCommand: public Command {
public:
    void execute(std::string& expression) override;
};

#endif // DELETECOMMAND_H
