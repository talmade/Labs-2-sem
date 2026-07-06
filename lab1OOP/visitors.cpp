#include <iostream>

#include "visitors.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

void PrintParamsShape::visit(const Circle& circle) {
    Point center = circle.getCenter();

    std::cout << "Circle name: " << circle.getName() << std::endl;
    std::cout << "Circle center coordinates: " << '\n'
              << "X: " << center.x << '\n'
              << "Y: " << center.y << std::endl;
    std::cout << "Circle radius: " << circle.getRadius() << std::endl;
}

void PrintParamsShape::visit(const Rectangle& rectangle) {
    Point uppLeft = rectangle.getUppLeft();
    Point downRight = rectangle.getDownRight();

    std::cout << "Rectangle name: " << rectangle.getName() << std::endl;
    std::cout << "Top left corner coordinates: " << '\n'
              << "X: " << uppLeft.x << '\n'
              << "Y: " << uppLeft.y << std::endl;
    std::cout << "Bottom right corner coordinates: " << '\n'
              << "X: " << downRight.x << '\n'
              << "Y: " << downRight.y << std::endl;
}

void PrintParamsShape::visit(const Triangle& triangle) {
    Point a = triangle.getA();
    Point b = triangle.getB();
    Point c = triangle.getC();

    std::cout << "Triangle name: " << triangle.getName() << '\n'
              << "First point coordinate: " << '\n'
              << "X: " << a.x << '\n'
              << "Y: " << a.y << '\n'
              << "Second point coordinate: " << '\n'
              << "X: " << b.x << '\n'
              << "Y: " << b.y << '\n'
              << "Third point coordinate: " << '\n'
              << "X: " << c.x << '\n'
              << "Y: " << c.y << std::endl;
}

void PrintPerimetrShape::visit(const Circle& circle) {
    std::cout <<"Circle name: " << circle.getName() << '\n'
              << "Circle perimetr: " << circle.getPerimetr() << std::endl;
}

void PrintPerimetrShape::visit(const Rectangle& rectangle) {
    std::cout << "Rectangle name: " << rectangle.getName() << '\n'
              << "Rectangle petimetr: " << rectangle.getPerimetr() << std::endl;
}

void PrintPerimetrShape::visit(const Triangle& triangle) {
    std::cout << "Triangle name: " << triangle.getName() << '\n'
              << "Triangle perimetr: " << triangle.getPerimetr() << std::endl;
}

void PrintNameShape::visit(const Circle& circle) {
    std::cout << "Circle name: " << circle.getName() << '\n'
              << "Type: Circle";
}

void PrintNameShape::visit(const Rectangle& rectangle) {
    std::cout << "Rectangle name: " << rectangle.getName() << '\n'
              << "Type: Rectangle";
}

void PrintNameShape::visit(const Triangle& triangle) {
    std::cout << "Rectangle name: " << triangle.getName() << '\n'
              << "Type: triangle";
}



