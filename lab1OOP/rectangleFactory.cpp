#include "rectangleFactory.h"
#include "shape.h"
#include "input.h"
#include "Rectangle.h"

Shape* RectangleFactory::create() {

    std::string name = inputName();

    while(true) {
        try {
            Point uppLeft = inputPoint("Enter top left angle: ");
            Point downRight = inputPoint("Enter bottom right angle: ");
            return new Rectangle(name, uppLeft, downRight);
        } catch (const std::invalid_argument& message) {
            std::cout << message.what() << std::endl;
        }
    }
}

