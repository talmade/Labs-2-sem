#include <string>
#include <stdexcept>
#include <cmath>

#include "circle.h"
#include "constants.h"

Circle::Circle(const std::string& name, const Point& center, const double& radius)
    : name(name), center(center), radius(radius) {
    if (radius <= 0)
        throw std::invalid_argument("Radius must be greater than zero!\n");
}

double Circle::getRadius() const {return radius;}

std::string Circle::getName() const {return name;}

double Circle::getPerimetr() const {
    return Constants::CONST_OF_AREA_CIRCLE * M_PI * radius;
}

Point Circle::getCenter() const {
    return center;
}

void Circle::accept(ShapeVisitor& visitor) const {
    visitor.visit(*this);
}
