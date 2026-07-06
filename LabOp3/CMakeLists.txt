cmake_minimum_required(VERSION 3.19)
project(LabOp3 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(LabOp3
    WIN32 MACOSX_BUNDLE
    ui/main.cpp
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
    logic/appContext.h
    logic/appParams.h
    logic/logicConstants.h
    logic/cvsParsing.h
    logic/cvsParsing.cpp
    logic/LinkedList.h
    logic/LinkedList.cpp
    logic/Iterator.h
    logic/Iterator.cpp
    logic/loadData.h
    logic/loadData.cpp
    logic/calculateMetric.h
    logic/calculateMetric.cpp
    logic/sort.h
    logic/sort.cpp
    logic/stringMemory.h
    logic/stringMemory.cpp
    entryPoint/entryPoint.h
    entryPoint/entryPoint.cpp
    ui/graphWindow.h
    ui/graphWindow.cpp
    logic/arrayUtils.h
    logic/arrayUtils.cpp
    ui/graphConstants.h
    logic/appContext.cpp
)

target_link_libraries(LabOp3
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS LabOp3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET LabOp3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
