cmake_minimum_required(VERSION 3.16)
project(tp1)

include_directories(google-test)
add_subdirectory(google-test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(
    tp1
    src/c++/main.cpp
    src/c++/partido.cpp
    src/c++/partido.h
    src/c++/funciones.hpp
    src/c++/defines.h
    src/c++/Season.hpp
)

add_executable(elimGaussTests ${SOURCE_FILES} testsC/elimGaussTests.cpp testsC/expecteds.h)
add_executable(solveSystemTests ${SOURCE_FILES} testsC/solveSystemTests.cpp testsC/expecteds.h)
add_executable(seasonTests ${SOURCE_FILES} testsC/seasonTests.cpp testsC/expecteds.h src/c++/partido.h src/c++/partido.cpp)


# Necesitamos asociar los archivos del framework de testing
target_link_libraries(elimGaussTests gtest gtest_main)
target_link_libraries(solveSystemTests gtest gtest_main)
target_link_libraries(seasonTests gtest gtest_main)
