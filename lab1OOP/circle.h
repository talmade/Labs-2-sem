#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>

#include "shape.h"
#include "point.h"

class Circle: public Shape
{
public:
    Circle(const std::string&, const Point&, const double&);

    std::string getName() const override;
    double getPerimetr() const override;
    double getRadius() const;
    Point getCenter() const;

    void accept(ShapeVisitor& visitor) const override;
private:
    std::string name;
    Point center;
    double radius;
};

#endif // CIRCLE_H
