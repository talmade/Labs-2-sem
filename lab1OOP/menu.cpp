#include <iostream>

#include "menu.h"
#include "constants.h"
#include "input.h"
#include "commands.h"

void runMenu(std::vector<MenuCommands*>& commands) {
    int number;

    do {
        for (unsigned i = 0; i < commands.size(); ++i)
            std::cout << i + Constants::MENU_INDEX_OFFSET << ". " << commands[i]->getLabel() << std::endl;
        std::cout << Constants::MENU_EXIT << ". Exit" << std::endl;

        number = inputNum<int>("Enter number: ");

        std::cout << '\n';

        if (number == Constants::MENU_EXIT) {

        } else if(number <= 0 || number > static_cast<int>(commands.size()))
            std::cout << "Invalid number" << std::endl;
        else {
            unsigned index = number - Constants::MENU_INDEX_OFFSET;
            commands[index]->execute();
        }
        std::cout << '\n';
    } while(number != Constants::MENU_EXIT);
}

std::vector<MenuCommands*> createCommands(std::vector<Shape*>& shapes) {
    std::vector<MenuCommands*> commands;

    commands.push_back(new AddCircleCommand(shapes));
    commands.push_back(new AddRectangleCommand(shapes));
    commands.push_back(new AddTriangleCommand(shapes));
    commands.push_back(new PrintParamsCommand(shapes));
    commands.push_back(new PrintPerimetrCommand(shapes));
    commands.push_back(new PrintTotalPerimetrCommand(shapes));
    commands.push_back(new SortCommand(shapes));
    commands.push_back(new DeleteByNumberCommand(shapes));
    commands.push_back(new DeleteByPerimetrCommand(shapes));
    commands.push_back(new PrintNameShapeCommand(shapes));

    return commands;
}
