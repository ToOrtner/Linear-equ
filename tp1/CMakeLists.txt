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

add_executable(correrTests ${SOURCE_FILES} src/c++/tests/elimGaussTests.cpp src/c++/tests/seasonTests.cpp src/c++/tests/solveSystemTests.cpp src/c++/tests/expecteds.h)

add_executable(elimGaussTests ${SOURCE_FILES} src/c++/tests/elimGaussTests.cpp src/c++/tests/expecteds.h)
add_executable(solveSystemTests ${SOURCE_FILES} src/c++/tests/solveSystemTests.cpp src/c++/tests/expecteds.h)



# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)
target_link_libraries(elimGaussTests gtest gtest_main)
target_link_libraries(solveSystemTests gtest gtest_main)


# Test suites a ejecutar
add_test(correrTests elimGaussTests seasonTests solveSystemTests tp1)
