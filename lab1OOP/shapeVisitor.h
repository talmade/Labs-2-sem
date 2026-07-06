#ifndef SHAPEVISITOR_H
#define SHAPEVISITOR_H

class Circle;
class Rectangle;
class Triangle;

class ShapeVisitor {
public:
    virtual void visit(const Circle&) = 0;
    virtual void visit(const Rectangle&) = 0;
    virtual void visit(const Triangle&) = 0;

    virtual ~ShapeVisitor() = default;
};

#endif // SHAPEVISITOR_H
