cmake_minimum_required(VERSION 3.19)
project(labOOP_3 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(labOOP_3
    WIN32 MACOSX_BUNDLE
    main.cpp
    ui/mainWindow.h
    ui/mainWindow.cpp
    ui/mainWindow.ui
    businessLogic/calculatorFacade.h
    businessLogic/calculatorFacade.cpp
    businessLogic/constantsLogic.h
    businessLogic/Operation/operator.h
    businessLogic/Operation/addOperator.h
    businessLogic/Operation/addOperator.cpp
    businessLogic/Operation/subtractOperator.h
    businessLogic/Operation/subtractOperator.cpp
    businessLogic/Operation/multiplyOperator.h
    businessLogic/Operation/multiplyOperator.cpp
    businessLogic/Operation/divideOperator.h
    businessLogic/Operation/divideOperator.cpp
    businessLogic/Operation/operatorFactory.h
    businessLogic/Operation/operatorFactory.cpp
    businessLogic/evalContext.h
    businessLogic/evalContext.cpp
    businessLogic/token/token.h
    businessLogic/token/numberToken.h
    businessLogic/token/numberToken.cpp
    businessLogic/token/operatorToken.h
    businessLogic/token/operatorToken.cpp
    businessLogic/token/binaryOperatorToken.h
    businessLogic/token/binaryOperatorToken.cpp
    businessLogic/token/leftParenToken.h
    businessLogic/token/leftParenToken.cpp
    businessLogic/token/rightParenToken.h
    businessLogic/token/rightParenToken.cpp
    businessLogic/tokenizer.h
    businessLogic/tokenizer.cpp
    businessLogic/evaluator.h
    businessLogic/evaluator.cpp
    businessLogic/commands/сommand.h
    businessLogic/commands/inputCommand.h
    businessLogic/commands/inputCommand.cpp
    businessLogic/commands/deleteCommand.h
    businessLogic/commands/deleteCommand.cpp
    businessLogic/commands/clearCommand.h
    businessLogic/commands/clearCommand.cpp
)

target_link_libraries(labOOP_3
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS labOOP_3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET labOOP_3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
