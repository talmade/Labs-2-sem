#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <string>

#include "Shape.h"
#include "menuCommands.h"

class AddCircleCommand: public MenuCommands {
public:
    AddCircleCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class AddRectangleCommand: public MenuCommands {
public:
    AddRectangleCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class AddTriangleCommand: public MenuCommands {
public:
    AddTriangleCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class PrintParamsCommand: public MenuCommands {
public:
    PrintParamsCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class PrintPerimetrCommand: public MenuCommands {
public:
    PrintPerimetrCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class PrintTotalPerimetrCommand: public MenuCommands {
public:
    PrintTotalPerimetrCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class SortCommand: public MenuCommands {
public:
    SortCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class DeleteByNumberCommand: public MenuCommands {
public:
    DeleteByNumberCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class DeleteByPerimetrCommand: public MenuCommands {
public:
    DeleteByPerimetrCommand(std::vector<Shape*>& shapes): shapes(shapes) {};

    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

class PrintNameShapeCommand: public MenuCommands {
public:
    PrintNameShapeCommand(std::vector<Shape*>& shapes): shapes(shapes) {};
    void execute() override;
    std::string getLabel() const override;
private:
    std::vector<Shape*>& shapes;
};

#endif // COMMANDS_H
