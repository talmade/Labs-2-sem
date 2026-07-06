#include "inputCommand.h"

InputCommand::InputCommand(std::string input) : input(std::move(input)) {}

void InputCommand::execute(std::string& expression) {
    expression += input;
}
