#ifndef SHAPE_H
#define SHAPE_H

#include <string>

#include "shapeVisitor.h"

class Shape {
public:
    virtual double getPerimetr() const = 0;
    virtual std::string getName() const = 0;
    virtual void accept(ShapeVisitor& visitor) const = 0;

    virtual ~Shape() = default;
};

#endif // SHAPE_H
