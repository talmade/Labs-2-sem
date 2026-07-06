#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

#include "commands.h"
#include "circleFactory.h"
#include "rectangleFactory.h"
#include "triangleFactory.h"
#include "visitors.h"
#include "constants.h"
#include "input.h"

std::string AddCircleCommand::getLabel() const {return "Add circle";}

void AddCircleCommand::execute() {
    try {
        CircleFactory factory;
        Shape* shape = factory.create();
        shapes.push_back(shape);
    } catch (const std::invalid_argument& message) {
        std::cout << message.what() << std::endl;
    }
}

std::string AddRectangleCommand::getLabel() const {return "Add rectangle";}

void AddRectangleCommand::execute() {
    try {
        RectangleFactory factory;
        Shape* shape = factory.create();
        shapes.push_back(shape);
    } catch (const std::invalid_argument& message) {
        std::cout << message.what() << std::endl;
    }
}

std::string AddTriangleCommand::getLabel() const {return "Add triangle";}

void AddTriangleCommand::execute() {
    try {
        TriangleFactory factory;
        Shape* shape = factory.create();
        shapes.push_back(shape);
    } catch (const std::invalid_argument& message) {
        std::cout << message.what() << std::endl;
    }
}

std::string PrintParamsCommand::getLabel() const {return "Print shapes parameters";}

void PrintParamsCommand::execute() {

    PrintParamsShape visitor;
    for (unsigned i = 0; i < shapes.size(); ++i) {
        std::cout << '\n';
        std::cout << i + Constants::MENU_INDEX_OFFSET << ". ";
        shapes[i]->accept(visitor);
    }
}

std::string PrintPerimetrCommand::getLabel() const {return "Print shapes perimetrs";}

void PrintPerimetrCommand::execute() {
    PrintPerimetrShape visitor;
    for (unsigned i = 0; i < shapes.size(); ++i) {
        std::cout << '\n';
        std::cout << i + Constants::MENU_INDEX_OFFSET << ". ";
        shapes[i]->accept(visitor);
    }
}

std::string PrintTotalPerimetrCommand::getLabel() const {return "Print total shapes perimetr";}

void PrintTotalPerimetrCommand::execute() {
    double totalPerimetr = 0;
    const int PRESICION = Constants::PRECISION_OF_A_NUMBER;

    for (unsigned i = 0; i < shapes.size(); ++i)
        totalPerimetr += shapes[i]->getPerimetr();

    std::cout << "Total perimetr of all shapes: " << std::fixed << std::setprecision(PRESICION) << totalPerimetr << std::endl;
}

std::string SortCommand::getLabel() const {return "Sort shapes";}

void SortCommand::execute() {
    std::sort(shapes.begin(), shapes.end(), [](const Shape* a, const Shape* b){
        return a->getPerimetr() < b->getPerimetr();
    });
}

std::string DeleteByNumberCommand::getLabel() const {return "Delete shape by number";}

void DeleteByNumberCommand::execute() {
    int number = inputNum<int>("Enter number: ");

    if (number <= 0 || number > static_cast<int>(shapes.size())) {
        std::cout << "Invalid number" << std::endl;
    } else {
        int index = number - Constants::MENU_INDEX_OFFSET;
        delete shapes[index];
        shapes.erase(shapes.begin() + index);
    }
}

std::string DeleteByPerimetrCommand::getLabel() const {return "Delete shapes with perimetr greater than specified";}

void DeleteByPerimetrCommand::execute() {
    double maxPerimetr = inputNum<double>("Enter perimetr: ");

    for (unsigned i = 0; i < shapes.size(); ++i)
        if (shapes[i]->getPerimetr() > maxPerimetr) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            --i;
        }
}

std::string PrintNameShapeCommand::getLabel() const {return "Print name and type shape";}

void PrintNameShapeCommand::execute() {
    PrintNameShape visitor;
    for (unsigned i = 0; i < shapes.size(); ++i) {
        std::cout << '\n';
        std::cout << i + Constants::MENU_INDEX_OFFSET << ". ";
        shapes[i]->accept(visitor);
        std::cout << '\n';
    }
}
