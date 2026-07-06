#include "deleteCommand.h"

void DeleteCommand::execute(std::string& expression) {
    if (!expression.empty())
        expression.pop_back();
}
