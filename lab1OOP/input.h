#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include <limits>

#include "point.h"

template<typename T>

T inputNum(const std::string& message) {
    T a;
    std::cout << message;
    while (!(std::cin >> a)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, please try again: ";
    }
    return a;
}

Point inputPoint(const std::string&);
std::string inputName();

#endif // INPUT_H
