#include "circleFactory.h"
#include "input.h"
#include "circle.h"

Shape* CircleFactory::create() {

    std::string name = inputName();
    Point center = inputPoint("Enter center coordinates: ");

    while (true) {
        try {
            double radius = inputNum<double>("Enter circle radius: ");
            return new Circle(name, center, radius);
        } catch (const std::invalid_argument& message) {
            std::cout << message.what() << std::endl;
        }
    }
}
