#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "shape.h"

class ShapeFactory {
public:
    virtual Shape* create() = 0;

    virtual ~ShapeFactory() = default;
};

#endif // SHAPEFACTORY_H
