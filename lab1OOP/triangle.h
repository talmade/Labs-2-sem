#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>

#include "point.h"
#include "shape.h"

class Triangle: public Shape
{
public:
    Triangle(const std::string&, const Point&, const Point&, const Point&);

    Point getA() const;
    Point getB() const;
    Point getC() const;
    std::string getName() const override;
    double getPerimetr() const override;

    void accept(ShapeVisitor& visitor) const override;
private:
    std::string name;
    Point a, b, c;

    static bool validTriangleCheck(const Point&, const Point&, const Point&);
    static double calculateSide(const Point&, const Point&);
};

#endif // TRIANGLE_H
