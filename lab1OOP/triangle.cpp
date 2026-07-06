#include <string>
#include <cmath>
#include <stdexcept>

#include "point.h"
#include "triangle.h"

Triangle::Triangle(const std::string& name, const Point& a, const Point& b, const Point& c)
    : name(name), a(a), b(b), c(c) {
    if (validTriangleCheck(a, b, c))
        throw std::invalid_argument("Cannot construct a triangle from the given coordinates!\n");
}

Point Triangle::getA() const {return a;}

Point Triangle::getB() const {return b;}

Point Triangle::getC() const {return c;}

std::string Triangle::getName() const {return name;}

bool Triangle::validTriangleCheck(const Point& a, const Point& b, const Point& c) {
    double ab = calculateSide(a, b);
    double bc = calculateSide(b, c);
    double ca = calculateSide(c, a);

    return ab + bc < ca || ab + ca < bc || bc + ca < ab;
}

double Triangle::calculateSide(const Point& a, const Point& b) {
    return hypot(b.x - a.x, b.y - a.y);
}

double Triangle::getPerimetr() const {
    return calculateSide(a, b) + calculateSide(b, c) + calculateSide(c, a);
}

void Triangle::accept(ShapeVisitor& visitor) const {
    visitor.visit(*this);
}
