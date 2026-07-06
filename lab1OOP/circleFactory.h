#ifndef CIRCLEFACTORY_H
#define CIRCLEFACTORY_H

#include "shapeFactory.h"

class CircleFactory: public ShapeFactory {
public:
    Shape* create() override;
};

#endif // CIRCLEFACTORY_H
