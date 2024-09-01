cmake_minimum_required(VERSION 3.20)

project(ResourceModule)

add_library(
    resource
    STATIC
    src/Mesh.cpp
    src/Transform.cpp
    src/ObjectInputHandler.cpp
    src/GameObject.cpp
)

target_include_directories(resource PUBLIC ../Main/include)
target_link_libraries(resource PUBLIC math)
target_link_directories(resource PUBLIC ../Math/bin)