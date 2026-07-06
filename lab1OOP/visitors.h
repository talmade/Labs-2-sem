#ifndef VISITORS_H
#define VISITORS_H

#include "shapeVisitor.h"

class PrintParamsShape: public ShapeVisitor {
public:
    void visit(const Circle&) override;
    void visit(const Rectangle&) override;
    void visit(const Triangle&) override;
};

class PrintPerimetrShape: public ShapeVisitor {
public:
    void visit(const Circle&) override;
    void visit(const Rectangle&) override;
    void visit(const Triangle&) override;
};

class PrintNameShape: public ShapeVisitor {
public:
    void visit(const Circle&) override;
    void visit(const Rectangle&) override;
    void visit(const Triangle&) override;
};

#endif // VISITORS_H
