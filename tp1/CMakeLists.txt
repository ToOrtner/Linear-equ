cmake_minimum_required(VERSION 3.16)
project(tp1)

include_directories(google-test)
add_subdirectory(google-test)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    tp1
    src/c++/main.cpp
    src/c++/partido.cpp
    src/c++/partido.h
    src/c++/funciones.cpp
    src/c++/defines.h
    src/c++/Season.hpp
)


add_executable(correrTests ${SOURCE_FILES} src/c++/tests.cpp)


# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)


# Test suites a ejecutar
add_test(correrTests tp1)
