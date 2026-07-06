#include "triangleFactory.h"
#include "input.h"
#include "triangle.h"

Shape* TriangleFactory::create() {

    std::string name = inputName();

    while(true) {
        try {
            Point a = inputPoint("Enter first coordinate: ");
            Point b = inputPoint("Enter second coordinate: ");
            Point c = inputPoint("Enter third coordinate: ");
            return new  Triangle(name, a, b, c);
        } catch (const std::invalid_argument& message) {
            std::cout << message.what() << std::endl;
        }
    }
}
