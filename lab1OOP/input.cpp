#include <iostream>

#include "input.h"

Point inputPoint(const std::string& message) {
    Point point;

    std::cout << message << "\n";
    point.x = inputNum<double>("X: ");
    point.y = inputNum<double>("Y: ");

    return point;
}

std::string inputName() {
    std::string name;

    std::cout << "Enter shape name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    return name;
}






