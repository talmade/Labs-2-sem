cmake_minimum_required(VERSION 3.16)

project(labOOP2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(labOOP2 main.cpp
    myset.h
    iterator.h
    myset.tpp
    iterator.tpp
    node.h
    node.tpp
    testset.h testset.cpp)

include(GNUInstallDirs)
install(TARGETS labOOP2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
