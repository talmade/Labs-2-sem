#ifndef RECTANGLEFACTORY_H
#define RECTANGLEFACTORY_H

#include "shapeFactory.h"

class RectangleFactory: public ShapeFactory {
public:
    Shape* create() override;
};

#endif // RECTANGLEFACTORY_H
