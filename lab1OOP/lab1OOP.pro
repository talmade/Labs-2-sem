TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        circle.cpp \
        circleFactory.cpp \
        commands.cpp \
        input.cpp \
        main.cpp \
        menu.cpp \
        rectangle.cpp \
        rectangleFactory.cpp \
        triangle.cpp \
        triangleFactory.cpp \
        visitors.cpp

HEADERS += \
    circle.h \
    circleFactory.h \
    commands.h \
    constants.h \
    input.h \
    menu.h \
    menuCommands.h \
    point.h \
    rectangle.h \
    rectangleFactory.h \
    shape.h \
    shapeFactory.h \
    shapeVisitor.h \
    triangle.h \
    triangleFactory.h \
    visitors.h

