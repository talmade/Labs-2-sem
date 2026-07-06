#ifndef MENU_H
#define MENU_H

#include <vector>

#include "menuCommands.h"
#include "shape.h"

void runMenu(std::vector<MenuCommands*>&);

std::vector<MenuCommands*> createCommands(std::vector<Shape*>&);

#endif // MENU_H
