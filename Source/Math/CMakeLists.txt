cmake_minimum_required(VERSION 3.20)

project(MathModule)

add_library(
    math 
    STATIC
    src/MathFunctions.cpp
    src/Vector2.cpp
    src/Vector3.cpp
    src/Vector4.cpp
    src/Matrix3x3.cpp)


target_include_directories(math PUBLIC ../Main/include)
target_link_libraries(math PUBLIC headers)
target_link_directories(math PUBLIC ../Main/bin)
