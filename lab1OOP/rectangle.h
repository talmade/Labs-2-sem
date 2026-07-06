#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>

#include "point.h"
#include "shape.h"

class Rectangle: public Shape
{
public:
    Rectangle(const std::string&, const Point&, const Point&);

    Point getUppLeft() const;
    Point getDownRight() const;
    std::string getName() const override;
    double getPerimetr() const override;

    void accept(ShapeVisitor& visitor) const override;
private:
    std::string name;
    Point uppLeft;
    Point downRight;
};

#endif // RECTANGLE_H
