#include <string>
#include <stdexcept>

#include "constants.h"
#include "rectangle.h"
#include "point.h"

Rectangle::Rectangle(const std::string& name, const Point& uppLeft, const Point& downRight)
    : name(name), uppLeft(uppLeft), downRight(downRight) {
    if (uppLeft.x > downRight.x)
        throw std::invalid_argument("Top left angle must be to the left of the bottom right angle\n");
    else if (uppLeft.y < downRight.y)
        throw std::invalid_argument("Top left angle must be above the bottom right angle!\n");
}

Point Rectangle::getUppLeft() const {return uppLeft;}

Point Rectangle::getDownRight() const {return downRight;}

std::string Rectangle::getName() const {return name;}

double Rectangle::getPerimetr() const {
    return Constants::CONST_OF_AREA_RECTANGLE * ((uppLeft.y - downRight.y) + (downRight.x - uppLeft.x));
}

void Rectangle::accept(ShapeVisitor& visitor) const {
    visitor.visit(*this);
}
