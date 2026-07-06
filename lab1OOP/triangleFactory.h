#ifndef TRIANGLEFACTORY_H
#define TRIANGLEFACTORY_H

#include "shapeFactory.h"

class TriangleFactory: public ShapeFactory {
public:
    Shape* create() override;
};

#endif // TRIANGLEFACTORY_H
