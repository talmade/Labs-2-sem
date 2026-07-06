cmake_minimum_required(VERSION 3.19)
project(lab4_op LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(lab4_op
    WIN32 MACOSX_BUNDLE
    logic/main.cpp
    ui/mainWindow.cpp
    ui/mainWindow.h
    ui/mainWindow.ui
    logic/appContext.h
    logic/csvParsing.cpp
    logic/csvParsing.h
    logic/matrixUtils.h
    logic/matrixUtils.cpp
    logic/stringUtils.h logic/stringUtils.cpp
    logic/normalizer.h
    logic/normalizer.cpp
    logic/transform.h
    logic/transform.cpp
    entryPoint.h
    entryPoint.cpp
    logic/statusCode.h
    logic/contextManager.h
    logic/contextManager.cpp
    ui/surfaceWidget.h ui/surfaceWidget.cpp
    logic/errorHandler.h
    logic/errorHandler.cpp
)

target_link_libraries(lab4_op
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS lab4_op
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET lab4_op
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
