#include <vector>

#include "shape.h"
#include "menu.h"

int main()
{
    std::vector<Shape*> shapes;
    std::vector<MenuCommands*> commands = createCommands(shapes);

    runMenu(commands);

    for (MenuCommands* command : commands)
        delete command;

    for (Shape* shape : shapes)
        delete shape;
}
